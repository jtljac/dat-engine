#include "../include/base-asset-processor.h"

#include <fstream>

using namespace AssetProcessor::Processors;

std::vector<char> IBaseAssetProcessor::readWholeFile(std::filesystem::path path) {
    std::ifstream stream;
    stream.exceptions(std::ifstream::badbit);

    stream.open(path, std::ios::binary | std::ios::ate);

    std::vector<char> data(stream.tellg());
    stream.seekg(0, std::ios::beg);
    stream.read(data.data(), data.size());

    return data;
}
void IBaseAssetProcessor::writeFileBuffer(std::filesystem::path dest, const char* data, size_t size) {
    std::ofstream stream;
    stream.exceptions(std::ofstream::badbit);

    stream.open(dest, std::ios::binary);
    stream.write(data, size);
}
