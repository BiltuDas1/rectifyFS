#pragma once

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include "../device/block_device.hpp"

constexpr uint32_t RECTIFYFS_MAGIC = 0x196B824;

struct BlockData {
  uint32_t magic = RECTIFYFS_MAGIC;
  uint32_t version = 0;
  uint32_t block_size = 0;
  uint64_t total_blocks = 0;

  uint32_t bitmap_start = 1;
};

class SuperBlock {
  public:
    explicit SuperBlock(BlockData data) : data(data) {}
    explicit SuperBlock() {}

    void read_superblock(BlockDevice& disk) {
      Block buffer = disk.read_block(0);
      std::memcpy(&this->data, buffer.data(), sizeof(this->data));

      if (this->data.magic != RECTIFYFS_MAGIC) {
        throw std::runtime_error("Invalid filesystem magic");
      }
    }

    void write_superblock(BlockDevice& disk) {
      if (this->data.total_blocks == 0) {
        throw std::runtime_error("no superblock to write");
      }

      Block buffer{};
      std::memcpy(buffer.data(), &this->data, sizeof(this->data));
      disk.write_block(0, buffer);
    }

    BlockData get() const {
      return this->data;
    }

  private:
    BlockData data;
};
