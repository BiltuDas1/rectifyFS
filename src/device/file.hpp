#pragma once

#include "block_device.hpp"
#include "../config/constrains.hpp"
#include <stdexcept>
#include <fstream>

/// @brief FileDevice allows reading/writing img file
class FileDevice : public BlockDevice {
  public:
    explicit FileDevice(const std::string& path) {
      file.open(
        path,
        std::ios::binary |
        std::ios::in |
        std::ios::out
      );

      if (!file.is_open()) {
        throw std::runtime_error("Failed to open disk image");
      }
    }

    Block read_block(BlockID id) override {
      const std::streamoff offset = get_offset(id);

      file.seekg(offset);
      file.read(reinterpret_cast<char*>(this->buffer.data()), BLOCK_SIZE);
      return this->buffer;
    }

    void write_block(BlockID id, const Block& block) override {
      const std::streamoff offset = get_offset(id);

      file.seekp(offset);
      file.write(reinterpret_cast<const char*>(block.data()), BLOCK_SIZE);
      file.flush();
    }

  private:
    std::fstream file;
    Block buffer;

    std::streamoff get_offset(BlockID id) {
      return static_cast<std::streamoff>(id) * BLOCK_SIZE;
    }
};