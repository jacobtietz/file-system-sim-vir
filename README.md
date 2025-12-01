# Virtual File System Simulation (VFS)

This project implements an **in-memory Virtual File System (VFS)** in C++17. It simulates the behavior of a basic file system, allowing file and directory operations without interacting with the host machine's real file system.  

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

Additional features include:

- **Mount Manager:** Allows multiple virtual file systems to be mounted at different mount points.
- **Directory Traversal:** Supports nested directories and file paths.
- **In-Memory Storage:** All data is stored in memory for fast operations without disk I/O.
- **Error Handling:** Graceful handling of invalid commands and paths.
- **Optional Enhancements:** Tree visualization and content editing.

---

## Project Structure

