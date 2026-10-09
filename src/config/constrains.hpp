#pragma once

#include <cstdint>

constexpr uint32_t BLOCK_SIZE = 4096;

using BlockID = uint64_t;
using Block = std::array<uint8_t, BLOCK_SIZE>;
