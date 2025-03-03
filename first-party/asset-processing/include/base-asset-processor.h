#pragma once

#include <filesystem>
#include <vector>

namespace AssetProcessor::Processors {
    /**
     * Interface for processing a file and converting it into an engine asset
     */
    class IBaseAssetProcessor {
    protected:
        virtual ~IBaseAssetProcessor() {};

        /**
         * Read the contents of a file into a vector buffer
         *
         * @param path The path to the file to read
         * @return The file content
         */
        static std::vector<char> readWholeFile(std::filesystem::path path);

        /**
         * Store the contents of a buffer into a file
         *
         * @param dest The destination to write the file
         * @param data The data to store in the file
         * @param size The length of the data being stored
         */
        static void writeFileBuffer(std::filesystem::path dest, const char* data, size_t size);
    public:
        /**
         * Get the engine-assets this Asset Processor can process
         *
         * @return The formats supported by this Asset Processor
         */
        virtual std::vector<std::string> getSupportedFormats() = 0;

        /**
         * Process the given file and write the result into the given output directory
         *
         * @param filePath The path to the file to process
         * @param dstDir The destination directory to write the processed asset result  to
         * @return A list of output files
         */
        virtual std::vector<std::filesystem::path> processFile(std::filesystem::path filePath, std::filesystem::path dstDir) = 0;
    };
}