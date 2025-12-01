#pragma once
#include "simple_fs.h"
#include <string>
#include <vector>
#include <memory>

struct Mount {
    std::string mount_point;
    std::shared_ptr<SimpleFS> fs;

    Mount(const std::string& p, std::shared_ptr<SimpleFS> f) : mount_point(p), fs(f) {}
};

class MountManager {
    std::vector<Mount> mounts;

public:
    void mount(std::shared_ptr<SimpleFS> fs, const std::string& path) {
        mounts.push_back(Mount(path, fs));
    }

    Mount* find_mount(const std::string& path) {
        for (auto& m : mounts) {
            if (path.find(m.mount_point) == 0) return &m;
        }
        return nullptr;
    }
};
