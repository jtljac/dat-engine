#include "../include/base-asset-processor.h"

#include <fstream>

using namespace AssetProcessor::Processors;

std::vector<char> IBaseAssetProcessor::readWholeStream(std::istream& stream) {
    stream.seekg(0, std::ios::end);
    std::vector<char> data(stream.tellg());
    stream.seekg(0, std::ios::beg);
    stream.read(data.data(), data.size());

    return data;
}

void IBaseAssetProcessor::writeStreamFromBuffer(std::ostream& stream, const char* data, size_t size) {
    stream.write(data, size);
}
