#pragma once
#include <stdexcept>

namespace DatEngine {
    class DatException : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };
} // namespace DatEngine
