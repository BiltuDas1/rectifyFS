#pragma once

#include "../config/constrains.hpp"
#include "../device/block_device.hpp"
#include <stdexcept>

class BitMap {
  public:
    explicit BitMap(BlockDevice& disk, BlockID start, uint64_t total_blocks)
    : start_block(start),
      total_blocks(total_blocks),
      disk(disk) {}

    void mark_unfree(BlockID block) {
      if (block >= total_blocks) {
        throw std::out_of_range("block position can't be more than total blocks");
      }

      BlockID block_pos = this->start_block + (block / (BLOCK_SIZE * 8));
      auto block_data = this->disk.read_block(block_pos);

      uint32_t pos = block % (BLOCK_SIZE * 8);
      uint32_t arr_index = pos / 8;
      uint32_t index_pos = pos % 8;

      block_data.at(arr_index) |= (1u << (7 - index_pos));

      this->disk.write_block(block_pos, block_data);
    }

    void mark_free(BlockID block) {
      if (block >= total_blocks) {
        throw std::out_of_range("block position can't be more than total blocks");
      }

      BlockID block_pos = this->start_block + (block / (BLOCK_SIZE * 8));
      auto block_data = this->disk.read_block(block_pos);

      uint32_t pos = block % (BLOCK_SIZE * 8);
      uint32_t arr_index = pos / 8;
      uint32_t index_pos = pos % 8;

      block_data.at(arr_index) &= ~(1u << (7 - index_pos));

      this->disk.write_block(block_pos, block_data);
    }

    bool isFree(BlockID block) {
      if (block >= total_blocks) {
        throw std::out_of_range("block position can't be more than total blocks");
      }

      BlockID block_pos = this->start_block + (block / (BLOCK_SIZE * 8));
      auto block_data = this->disk.read_block(block_pos);

      uint32_t pos = block % (BLOCK_SIZE * 8);
      uint32_t arr_index = pos / 8;
      uint32_t index_pos = pos % 8;

      uint8_t result = block_data.at(arr_index) & (1u << (7 - index_pos));
      return result == 0;
    }

  private:
    BlockID start_block;
    BlockID total_blocks;
    BlockDevice& disk;
};