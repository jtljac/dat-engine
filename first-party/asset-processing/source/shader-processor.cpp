#include "../include/shader-processor.h"

#include <fstream>
#include <iostream>

#include <glslang/SPIRV/GlslangToSpv.h>
#include <glslang/Public/ResourceLimits.h>

#include "asset-process-exception.h"

using namespace AssetProcessor::Processors;

/* -------------------------------------------- */
/* DatShaderIncluder                            */
/* -------------------------------------------- */

glslang::TShader::Includer::IncludeResult* DatIncluder::buildIncludeResult(const std::filesystem::path& path) {
    std::ifstream stream(path, std::ios::binary | std::ios::ate);
    std::size_t size = stream.tellg();

    stream.seekg(0, std::ios::beg);

    char* buffer = new char[size];
    stream.read(buffer, size);

    return new IncludeResult(path.string(), buffer, size, nullptr);
}

glslang::TShader::Includer::IncludeResult* DatIncluder::includeSystem(const char* headerName,
                                                                      const char* includerName,
                                                                      size_t inclusionDepth) {
    for (auto include : includes) {
        include /= headerName;

        if (exists(include)) {
            return buildIncludeResult(include);
        }
    }

    return nullptr;
}

glslang::TShader::Includer::IncludeResult* DatIncluder::includeLocal(const char* headerName,
                                                                     const char* includerName,
                                                                     size_t inclusionDepth) {
    std::filesystem::path path(includerName);
    path = path.parent_path() / headerName;

    if (exists(path)) {
        return buildIncludeResult(path);
    }
}

void DatIncluder::releaseInclude(IncludeResult* result) {
    delete[] result->headerData;
    delete result;
}

EShLanguage ShaderProcessor::getStageFromExtension(const std::string& extension) {
    if (extension == ".vert") {
        return EShLangVertex;
    } if (extension == ".geom") {
        return EShLangGeometry;
    } if (extension == ".comp") {
        return EShLangCompute;
    }

    return EShLangFragment;
}

/* -------------------------------------------- */
/* ShaderProcessor                              */
/* -------------------------------------------- */

std::vector<std::string> ShaderProcessor::getSupportedFormats() {
    return {"vert", "frag", "geom", "comp", "shader", "glsl"};
}

std::vector<std::filesystem::path>
ShaderProcessor::processFile(std::filesystem::path filePath, std::filesystem::path dstDir) {
    const std::vector<char> fileData = readWholeFile(filePath);

    const EShLanguage stage = getStageFromExtension(filePath.extension());
    glslang::TShader shader(stage);

    const char* strings[] = {fileData.data()};
    shader.setStrings(strings, 1);

    shader.setEnvClient(glslang::EShClientVulkan, glslang::EShTargetVulkan_1_4);
    shader.setEnvTarget(glslang::EshTargetSpv, glslang::EShTargetSpv_1_3);
    shader.setEntryPoint("main");

    auto messages = static_cast<EShMessages>(EShMsgDefault | EShMsgVulkanRules | EShMsgSpvRules);
    if (!shader.parse(GetDefaultResources(), 450, ENoProfile, false, false, messages, datIncluder)) {
        throw Exception::AssetProcessingException(shader.getInfoLog(), filePath);
    }

    glslang::TProgram program;
    program.addShader(&shader);
    if (!program.link(messages)) {
        throw Exception::AssetProcessingException(program.getInfoLog(), filePath);
    }

    glslang::TIntermediate& intermediate = *program.getIntermediate(stage);
    glslang::SpvOptions options = {.validate = true};
    std::vector<uint32_t> spirv;
    GlslangToSpv(intermediate, spirv, &options);

    std::filesystem::path shaderPath = dstDir / (filePath.filename().string() + ".spv");
    writeFileBuffer(shaderPath, reinterpret_cast<const char*>(spirv.data()), spirv.size() * sizeof(uint32_t));

    return {shaderPath};
}
