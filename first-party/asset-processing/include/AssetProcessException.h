#pragma once

#include <filesystem>
#include <stdexcept>
namespace AssetProcessor::Exception {
    /**
     * An exception representing a failure whilst processing an asset
     */
    class AssetProcessingException : public std::runtime_error {
    public:
        /** The path to the asset that failed to be processed */
        const std::filesystem::path assetPath;

        AssetProcessingException(const std::string& __arg, const std::filesystem::path& assetPath) :
            runtime_error(__arg), assetPath(assetPath) {}
        AssetProcessingException(const char* string, const std::filesystem::path& assetPath) :
            runtime_error(string), assetPath(assetPath) {}
        AssetProcessingException(runtime_error&& runtimeError, const std::filesystem::path& assetPath) :
            runtime_error(runtimeError), assetPath(assetPath) {}
        AssetProcessingException(const runtime_error& runtimeError, const std::filesystem::path& assetPath) :
            runtime_error(runtimeError), assetPath(assetPath) {}
    };
}