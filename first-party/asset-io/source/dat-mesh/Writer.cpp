#include "dat-mesh/Writer.h"

#include <ostream>

DatAssetIO::AssetIOResult DatAssetIO::DatMesh::writeHeader(
        std::ostream& stream,
        const uint8_t vertexSize,
        const uint32_t numVertices,
        const uint32_t numIndices,
        const uint8_t numTypeHints
) {
    stream.write(reinterpret_cast<const char*>(FILE_SIGNATURE), 8);
    stream.write(reinterpret_cast<const char*>(FILE_VERSION), 1);

    stream.write(reinterpret_cast<const char*>(&vertexSize), 1);
    stream.write(reinterpret_cast<const char*>(&numVertices), sizeof(uint32_t));
    stream.write(reinterpret_cast<const char*>(&numIndices), sizeof(uint32_t));
    stream.write(reinterpret_cast<const char*>(&numTypeHints), 1);

    return AssetIOResult::SUCCESS;
}
DatAssetIO::AssetIOResult DatAssetIO::DatMesh::writeDatMesh(
        std::ostream& stream,
        const uint8_t vertexSize,
        const std::vector<uint8_t>& vertices,
        const std::vector<uint32_t>& indices,
        const std::vector<TypeHint>* typeHints
) {
    const AssetIOResult headerResult = writeHeader(
            stream,
            vertexSize,
            vertices.size() / vertexSize,
            indices.size(),
            typeHints != nullptr ? typeHints->size() : 0
    );

    if (headerResult != AssetIOResult::SUCCESS) {
        return headerResult;
    }

    if (typeHints != nullptr) {
        stream.write(reinterpret_cast<const char*>(typeHints->data()), typeHints->size());
    }

    stream.write(reinterpret_cast<const char*>(vertices.data()), vertices.size());
    stream.write(reinterpret_cast<const char*>(indices.data()), indices.size() * sizeof(uint32_t));

    return AssetIOResult::SUCCESS;
}
