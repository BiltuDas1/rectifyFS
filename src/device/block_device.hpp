#pragma once

#include <array>
#include "../config/constrains.hpp"

class BlockDevice {
  public:
    virtual Block read_block(BlockID id) = 0;
    virtual void write_block(BlockID id, const Block& block) = 0;

    virtual ~BlockDevice() = default;
};
