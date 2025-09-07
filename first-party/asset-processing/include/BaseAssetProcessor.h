#pragma once

#include <filesystem>
#include <vector>
#include <algorithm>

namespace AssetProcessor::Processors {
    /**
     * Interface for processing a file and converting it into an engine asset
     */
    class IBaseAssetProcessor {
    protected:
        /**
         * Read the contents of a file into a vector buffer
         *
         * @param stream the stream to read from
         * @return The file content
         */
        static std::vector<char> readWholeStream(std::istream& stream);

        /**
         * Store the contents of a buffer into a file
         *
         * @param stream The destination to write the file
         * @param data The data to store in the file
         * @param size The length of the data being stored
         */
        static void writeStreamFromBuffer(std::ostream& stream, const char* data, size_t size);
    public:
        virtual ~IBaseAssetProcessor() = default;
        /**
         * Get A friendly name for this asset processor
         *
         * @return The name of this processor
         */
        virtual std::string getProcessorName() = 0;

        /**
         * Get the engine-assets this Asset Processor can process
         *
         * @return The file extensions supported by this Asset Processor
         */
        virtual std::vector<std::string> getSupportedFormats() = 0;

        /**
         * Get a suggested file name for the output of this asset processor
         *
         * @param originalFileName The filename (including extension) of the file before conversion
         * @return The suggested filename
         */
        virtual std::string suggestFileName(const std::string& originalFileName) = 0;

        /**
         * Check if a file extension is supported by this asset processor
         *
         * @param format The file extension to check for support (expects not to start with a period (".")
         * @return @code true@endcode when the extension is supported
         */
        virtual bool supportsFormat(const std::string& format) {
            std::vector<std::string> formats = getSupportedFormats();

            return formats.empty() || std::ranges::find(formats, format) != formats.end();
        }

        /**
         * Process the given file and write the result into the given output directory
         *
         * @param filePath The path of the file being processed
         * @param input an input stream reading the file
         * @param output an output stream to write the converted file to
         */
        virtual void processFile(const std::filesystem::path& filePath, std::istream& input, std::ostream& output) = 0;
    };
}