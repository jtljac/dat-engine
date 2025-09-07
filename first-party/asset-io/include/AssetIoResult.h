#pragma once

namespace DatAssetIO {
    /**
     * Return codes for Asset IO Operations
     */
    enum class AssetIOResult {
        SUCCESS = 0,
        INVALID_SIGNATURE = 1,
        VERSION_MISMATCH = 2,
        CORRUPT_FILE = 3
    };
}