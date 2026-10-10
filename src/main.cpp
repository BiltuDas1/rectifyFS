#include "device/block_device.hpp"
#include "device/file.hpp"
#include "lib/superblock.hpp"
#include "lib/bitmap.hpp"
#include "lib/block_allocator.hpp"
#include <cstring>
#include <iostream>

int main() {
  try {
    FileDevice device("filesystem.img");
    BlockDevice& disk = device;
    
    SuperBlock block;
    block.read_superblock(disk);

    auto superblock = block.get();
    BitMap map(disk, superblock.bitmap_start, superblock.total_blocks);

    BlockAllocator alloc(block, map);

    // for (int i = 70; i > 2; i--) {
    //   map.mark_free(i);
    // }

    // Block buffer{};
    // const char* message = "Hello";
    // std::memcpy(buffer.data(), message, std::strlen(message) + 1);
    // disk.write_block(50, buffer);
    // map.mark_unfree(5000);

    // std::cout << alloc.allocate_block() << std::endl;
    std::cout << map.isFree(3) << std::endl;


  } catch (const std::exception& e) {
    std::cerr
      << "Error: "
      << e.what()
      << '\n';

    return 1;
  }

  return 0;
}