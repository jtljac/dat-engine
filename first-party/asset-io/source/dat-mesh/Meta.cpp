#include "dat-mesh/Meta.h"

DatAssetIO::DatMesh::TypeHint DatAssetIO::DatMesh::getPrimitiveTypeHint(const TypeHint typeHint) {
    return static_cast<TypeHint>(static_cast<uint8_t>(typeHint) & 0b00001111);
}

uint32_t DatAssetIO::DatMesh::getPrimitiveSize(const TypeHint typeHint) {
    return 1 << ((static_cast<uint32_t>(typeHint) & 0b11000000) >> 6);
}

uint32_t DatAssetIO::DatMesh::getComponentCount(const TypeHint typeHint) {
    return ((static_cast<uint32_t>(typeHint) & 0b00110000) >> 4) + 1;
}
