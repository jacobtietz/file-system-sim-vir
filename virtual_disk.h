#pragma once
#include <vector>
#include <cstdint>

struct VirtualDisk {
    int num_blocks;
    int block_size;
    std::vector<std::vector<char>> blocks;
    // Represents the in-memory storage of the virtual disk as a 2D array of bytes.
    // Each inner vector is a block, simulating how data is stored on a real disk.
    // Constructor initializes the disk with the specified number of blocks and block size.
    VirtualDisk(int n_blocks, int b_size)
        : num_blocks(n_blocks), block_size(b_size), blocks(n_blocks, std::vector<char>(b_size, 0)) {}
};
