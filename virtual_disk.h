#pragma once
#include <vector>
#include <cstdint>

struct VirtualDisk {
    int num_blocks;
    int block_size;
    std::vector<std::vector<char>> blocks;

    VirtualDisk(int n_blocks, int b_size)
        : num_blocks(n_blocks), block_size(b_size), blocks(n_blocks, std::vector<char>(b_size, 0)) {}
};
