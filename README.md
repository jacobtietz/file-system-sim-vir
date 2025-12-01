# Virtual File System Simulation (VFS)

This project implements an **in-memory Virtual File System (VFS)** in C++17. It simulates the behavior of a basic file system, allowing file and directory operations in-memory through virtualization.

---

## Features

The VFS supports the following commands:

| Command | Description |
|---------|-------------|
| `ls <path>` | List directory contents |
| `mkdir <path>` | Create a new directory |
| `cat <path>` | Display the contents of a file |
| `write <path> <content>` | Overwrite or create a file with specified content |
| `append <path> <content>` | Append content to an existing file |
| `rm <path>` | Remove a file or directory |
| `tree <path>` | Display the directory tree from a given path |
| `exit` | Exit the VFS program |

---
