#pragma once

#include "base-asset-processor.h"

#include <glslang/Public/ShaderLang.h>

#include <filesystem>
#include <vector>

namespace AssetProcessor::Processors {
    /**
     * Simple implementation of GLSLang includer
     */
    class DatIncluder : public glslang::TShader::Includer {
    protected:
        /**
         * A list of directories to resolve system includes from
         */
        std::vector<std::filesystem::path> includes;

        /**
         * Build a IncludeResult with a valid path
         *
         * @param path The path to the file to include
         * @return An initialised IncludeResult
         */
        IncludeResult* buildIncludeResult(const std::filesystem::path& path);
    public:
        DatIncluder(const std::vector<std::filesystem::path>& includes) : includes(includes) {}

        IncludeResult* includeSystem(const char*, const char*, size_t) override;
        IncludeResult* includeLocal(const char*, const char*, size_t) override;
        void releaseInclude(IncludeResult*) override;
    };

    class ShaderProcessor : public IBaseAssetProcessor {
    protected:
        /** Includer for this shader processor */
        DatIncluder datIncluder;

        /** Get the shader stage from the file extension */
        EShLanguage getStageFromExtension(const std::string& extension);
    public:
        /**
         * @param includePaths A set of paths to search for system include paths
         */
        ShaderProcessor(const std::vector<std::filesystem::path>& includePaths) : datIncluder(includePaths) {};

        ~ShaderProcessor() override {};

        std::string getProcessorName() override { return "Shader Processor"; }
        std::vector<std::string> getSupportedFormats() override;
        std::string suggestFileName(const std::string& originalFileName) override;
        void processFile(const std::filesystem::path& filePath, std::istream& input, std::ostream& output) override;
    };
}