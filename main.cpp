// g++ -std=c++17 main.cpp simple_fs.h virtual_disk.h mount_manager.h -o vfs_test
// ./vfs_test

#include "simple_fs.h"
#include <iostream>
#include <sstream>
#include <memory>

int main() {
    auto fs = std::make_shared<SimpleFS>(nullptr);

    std::cout << "In-memory VFS initialized. Type 'help' for commands.\n";

    std::string line;
    while (true) {
        std::cout << "vfs$ ";
        if (!getline(std::cin, line)) break;
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        try {
            if (cmd == "exit") break;
            else if (cmd == "help") {
                std::cout << "Commands:\n";
                std::cout << "  ls <path>          : List directory contents\n";
                std::cout << "  mkdir <path>       : Create a directory\n";
                std::cout << "  cat <path>         : Display file contents\n";
                std::cout << "  write <path> <c>   : Overwrite/create file\n";
                std::cout << "  append <path> <c>  : Append to file\n";
                std::cout << "  rm <path>          : Remove file/directory\n";
                std::cout << "  tree <path>        : Show directory tree\n";
                std::cout << "  exit               : Exit VFS\n";
            }
            else if (cmd == "ls") {
                std::string path; iss >> path;
                if (path.empty()) path = "/";
                fs->list_dir(path);
            }
            else if (cmd == "mkdir") {
                std::string path; iss >> path;
                fs->create_dir(path);
            }
            else if (cmd == "cat") {
                std::string path; iss >> path;
                std::cout << fs->read_file(path) << "\n";
            }
            else if (cmd == "write") {
                std::string path; iss >> path;
                std::string content;
                getline(iss, content);
                if (!content.empty() && content[0] == ' ') content.erase(0,1); // remove leading space
                fs->write_file(path, content);
            }
            else if (cmd == "append") {
                std::string path; iss >> path;
                std::string content;
                getline(iss, content);
                if (!content.empty() && content[0] == ' ') content.erase(0,1); // remove leading space
                std::string old = fs->read_file(path);
                fs->write_file(path, old + content);
            }
            else if (cmd == "rm") {
                std::string path; iss >> path;
                fs->remove(path);
            }
            else if (cmd == "tree") {
                std::string path; iss >> path;
                Node* node = fs->traverse(path);
                if (!node) throw std::runtime_error("Path not found");
                fs->tree_print(node);
            }
            else {
                std::cout << "Unknown command\n";
            }
        } catch (std::exception &e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    std::cout << "Exiting VFS.\n";
    return 0;
}
