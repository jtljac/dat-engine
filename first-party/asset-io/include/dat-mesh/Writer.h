#pragma once

#include <iosfwd>
#include <vector>

#include "../AssetIoResult.h"
#include "Meta.h"

namespace DatAssetIO::DatMesh {
    /**
     * Write out the DatMesh header to the stream.
     *
     * This assumes that the stream is at position 0 before writing.
     *
     * @param stream The stream to write to
     * @param vertexSize The size of each vertex
     * @param numVertices The number of vertices
     * @param numIndices The number of indices
     * @param numTypeHints The number of type hints (Optional: Set to 0 to disable)
     * @return Result of writing
     */
    AssetIOResult writeHeader(std::ostream& stream, uint8_t vertexSize, uint32_t numVertices, uint32_t numIndices, uint8_t numTypeHints);

    // write body
    AssetIOResult writeDatMesh(std::ostream& stream, uint8_t vertexSize,
            const std::vector<uint8_t>& vertices,
            const std::vector<uint32_t>& indices,
            const std::vector<TypeHint>* typeHints);
    
}