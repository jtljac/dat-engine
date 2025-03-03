#pragma once

#include "base-asset-processor.h"

namespace AssetProcessor::Processors {
    /**
     * An implementation of IBaseAssetProcessor that simply copies the source file to its destination with no further
     * processing
     *
     * This supports all file types, and can be used as a fallback when no other Asset Processors handle the file
     */
    class CopyProcessor : public IBaseAssetProcessor {
    public:
        CopyProcessor() = default;
        virtual ~CopyProcessor() = default;

        std::vector<std::string> getSupportedFormats() override;
        std::vector<std::filesystem::path> processFile(std::filesystem::path filePath, std::filesystem::path dstDir) override;
    };
}