#pragma once

#include "superblock.hpp"
#include "bitmap.hpp"
#include "../config/constrains.hpp"


class BlockAllocator {
  public:
    explicit BlockAllocator(SuperBlock& block, BitMap& map) 
      : superblock(block), bitmap(map) {}

    BlockID allocate_block() {
      auto block = superblock.get();
      for (uint64_t i = 0; i < block.total_blocks; i++) {
        if (bitmap.isFree(i)) {
          bitmap.mark_unfree(i);
          return i;
        }
      }
      throw std::runtime_error("No free blocks available");
    }

    void free_block(BlockID block) {
      bitmap.mark_free(block);
    }

  private:
    SuperBlock superblock;
    BitMap bitmap;
};
