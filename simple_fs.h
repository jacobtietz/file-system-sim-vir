#pragma once
#include "virtual_disk.h"
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>

struct Node {
    bool is_dir;
    std::string name;
    std::string content;                 // Only used if is_dir == false
    std::map<std::string, Node> children;

    // Default constructor (needed for std::map)
    Node() : is_dir(false), name("") {}

    Node(std::string n, bool dir) : name(n), is_dir(dir) {}
};

class SimpleFS {
    std::shared_ptr<VirtualDisk> disk;
    Node root;

public:
    SimpleFS(std::shared_ptr<VirtualDisk> d) : disk(d), root("/", true) {}

    Node* traverse(const std::string& path) {
        if (path.empty() || path[0] != '/')
            throw std::runtime_error("Path must be absolute");

        Node* current = &root;
        if (path == "/") return current;

        size_t start = 1;
        size_t end = path.find('/', start);
        while (start < path.size()) {
            std::string part = path.substr(start, end - start);
            if (current->children.find(part) == current->children.end())
                return nullptr;
            current = &current->children[part];

            if (end == std::string::npos) break;
            start = end + 1;
            end = path.find('/', start);
        }
        return current;
    }

    void create_dir(const std::string& path) {
        size_t pos = path.find_last_of('/');
        std::string parent_path = (pos == 0) ? "/" : path.substr(0, pos);
        std::string dir_name = path.substr(pos + 1);

        Node* parent = traverse(parent_path);
        if (!parent || !parent->is_dir)
            throw std::runtime_error("Parent directory not found");

        parent->children[dir_name] = Node(dir_name, true);
    }

    void create_file(const std::string& path) {
        size_t pos = path.find_last_of('/');
        std::string parent_path = (pos == 0) ? "/" : path.substr(0, pos);
        std::string file_name = path.substr(pos + 1);

        Node* parent = traverse(parent_path);
        if (!parent || !parent->is_dir)
            throw std::runtime_error("Parent directory not found");

        parent->children[file_name] = Node(file_name, false);
    }

    void write_file(const std::string& path, const std::string& content) {
        Node* node = traverse(path);
        if (!node) {
            create_file(path);
            node = traverse(path);
        }
        if (!node || node->is_dir)
            throw std::runtime_error("Cannot write to directory");
        node->content = content;
    }

    std::string read_file(const std::string& path) {
        Node* node = traverse(path);
        if (!node || node->is_dir)
            throw std::runtime_error("File not found or is directory");
        return node->content;
    }

    void list_dir(const std::string& path) {
        Node* node = traverse(path);
        if (!node || !node->is_dir)
            throw std::runtime_error("Directory not found");

        for (auto& [name, child] : node->children) {
            std::cout << (child.is_dir ? "[D] " : "[F] ") << name << "\n";
        }
    }

    void remove(const std::string& path) {
        size_t pos = path.find_last_of('/');
        std::string parent_path = (pos == 0) ? "/" : path.substr(0, pos);
        std::string name = path.substr(pos + 1);

        Node* parent = traverse(parent_path);
        if (!parent || parent->children.find(name) == parent->children.end())
            throw std::runtime_error("Entry not found");

        parent->children.erase(name);
    }

    void tree_print(Node* node = nullptr, std::string prefix = "") {
        if (!node) node = &root;
        std::cout << prefix << node->name << (node->is_dir ? "/" : "") << "\n";
        for (auto& [name, child] : node->children) {
            tree_print(&child, prefix + "  ");
        }
    }
};
