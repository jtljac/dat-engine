#pragma once

#include "../AssetIoResult.h"
#include "Meta.h"

#include <vector>
#include <iostream>

namespace DatAssetIO::DatMesh {
    /**
     * Reads a DatMesh header from the stream
     *
     * This assumes that the stream is at position 0 of the DatMesh file/buffer. After reading, the stream will be
     * positioned on the first byte after the header.
     *
     * @param buffer The buffer to read from
     * @param header A structure to write the header into
     * @return Result of reading
     */
    AssetIOResult readDatMeshHeader(std::istream& buffer, DatMeshHeader& header);

    /**
     * Reads the contents of a DatMesh file into buffers
     *
     * This will reset the buffer to the beginning before reading. After reading, the stream will be positioned at the
     * end of the stream.
     *
     * @param buffer The buffer to read from
     * @param vertices A vector to store the resulting vertices in
     * @param indices A vector to store the resulting indices in
     * @param typeHints A vector to store the resulting typeHints in, can be nullptr to ignore
     * @return Result of reading
     */
    AssetIOResult readDatMesh(std::istream& buffer, std::vector<uint8_t>& vertices, std::vector<uint32_t>& indices, std::vector<TypeHint>* typeHints);
}