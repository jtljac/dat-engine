#include "../../include/dat-mesh/reader.h"

#include <cassert>
#include <istream>
#include <streambuf>
#include <vector>

using namespace DatAssetIO::DatMesh;

DatAssetIO::AssetIOResult DatAssetIO::DatMesh::readDatMeshHeader(std::istream& buffer, DatMeshHeader& header) {
    buffer.read(reinterpret_cast<char*>(&header.signature), 8);
    if (!std::equal<uint8_t>(FILE_SIGNATURE[0], FILE_SIGNATURE[8], header.signature[0]))
        return AssetIOResult::INVALID_SIGNATURE;

    buffer.read(reinterpret_cast<char*>(&header.version), 1);
    if (header.version != FILE_VERSION) return AssetIOResult::VERSION_MISMATCH;

    buffer.read(reinterpret_cast<char*>(header.vertexSize), 1);
    buffer.read(reinterpret_cast<char*>(header.vertexCount), sizeof(uint32_t));
    buffer.read(reinterpret_cast<char*>(header.indexCount), sizeof(uint32_t));
    buffer.read(reinterpret_cast<char*>(header.typeHintSize), 1);

    return AssetIOResult::SUCCESS;
}

DatAssetIO::AssetIOResult DatAssetIO::DatMesh::readDatMesh(std::istream& buffer, std::vector<uint8_t>& vertices, std::vector<uint32_t>& indices, std::vector<TypeHint>* typeHints) {
    buffer.seekg(0);

    DatMeshHeader header;
    const AssetIOResult headerResult = readDatMeshHeader(buffer, header);
    if (headerResult != AssetIOResult::SUCCESS) {
        return headerResult;
    };

    if (typeHints != nullptr) {
        typeHints->resize(header.typeHintSize);
        buffer.read(reinterpret_cast<char*>(typeHints->data()), header.typeHintSize);
    } else {
        buffer.seekg(header.typeHintSize, std::ios::cur);
    }

    vertices.resize(header.vertexCount);
    buffer.read(reinterpret_cast<char*>(vertices.data()), header.vertexSize * header.vertexCount);
    indices.resize(header.indexCount);
    buffer.read(reinterpret_cast<char*>(indices.data()), header.indexCount * sizeof(uint32_t));

    if(buffer.eof()) return AssetIOResult::CORRUPT_FILE;

    return AssetIOResult::SUCCESS;
}
