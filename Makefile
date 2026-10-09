CXX = g++
CXXFLAGS = -std=c++20 -Wall -Werror -Wextra -pedantic

SRC = $(wildcard src/*.cpp)

TARGET_DIR = data
TARGET = $(TARGET_DIR)/myfs

FS_IMAGE = $(TARGET_DIR)/filesystem.img
FS_SIZE_MB = 10

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p $(TARGET_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

run: $(TARGET)
	cd $(TARGET_DIR) && ./myfs

createfs:
	mkdir -p $(TARGET_DIR)
	dd if=/dev/zero of=$(FS_IMAGE) bs=1M count=$(FS_SIZE_MB) status=progress

clean:
	rm -f $(TARGET)
	rm -f $(FS_IMAGE)

.PHONY: all run createfs clean