#include "../include/copy-processor.h"

std::vector<std::string> AssetProcessor::Processors::CopyProcessor::getSupportedFormats() { return {}; }

std::vector<std::filesystem::path> AssetProcessor::Processors::CopyProcessor::processFile(
        const std::filesystem::path filePath,
        const std::filesystem::path dstDir
) {
    std::filesystem::path dstFile = dstDir / filePath.filename();
    copy(filePath, dstFile);

    return {dstFile};
}
