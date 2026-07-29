# 06_Filesystem

This project demonstrates the C++17 `<filesystem>` library with practical utilities for path manipulation, directory and file operations, recursive traversal, normalization, and temporary file management. Examples show safe usage patterns, error handling, and testable behaviors.

Overview
- Purpose and scenarios
  - Provide small, focused utilities that wrap `std::filesystem` for common tasks: combining paths, extracting extensions, creating directories, creating and removing files, listing directory contents, recursive file searches, and temporary file handling.
  - Useful for test harnesses, tooling, build utilities, and examples teaching safe filesystem practices.
- Key concepts demonstrated
  - Safe path composition using `operator/` and `std::filesystem::path` to avoid manual string concatenation and platform pitfalls.
  - Scoped temporary directories: creating test directories under the system temporary folder and ensuring deterministic cleanup (RAII).
  - Existence checks and idempotent directory creation (`exists`, `create_directory`, `create_directories`).
  - File operations that consider errors and exceptions (`file_size`, `remove`, `filesystem_error`) and guard accordingly.
  - Directory iteration (`directory_iterator` for non-recursive listing and `recursive_directory_iterator` for recursive searches) with filters for regular files.
  - Path normalization and canonicalization to handle redundant components or different path formats.
- Safety and portability notes
  - Prefer `std::filesystem` operations over manual file APIs to improve cross‑platform correctness.
  - Catch and handle `std::filesystem::filesystem_error` where operations may fail (permissions, concurrent deletion, etc.).
  - Use system temporary directory (`std::filesystem::temp_directory_path()`) for test artifacts to reduce risk of accidental data loss; isolate test folders using unique names.
- Testing guidance
  - Tests included show creating a temporary base directory, verifying existence, creating files and subdirectories, enumerating files, checking file sizes, and ensuring cleanup removes test artifacts.
  - Tests reconstruct the expected base path from `temp_directory_path()` for independent verification.

Project contents (high level)
- `Filesystem_Basic.h` / `Filesystem_Basic.cpp`
  - `Filesystem_Basic` wraps:
    - constructor that creates a base temp directory,
    - `getExtension(subDir, filename)`,
    - `createDir(relativePath)`,
    - `createAndRemoveFile(filename, content)` returning the created file size,
    - `listFilesInBaseDir()` that returns filenames in the base directory,
    - destructor/`cleanup()` that removes the base directory recursively.
- `Filesystem_Advance.h` / corresponding implementation
  - `Filesystem_Advance` exposes:
    - recursive search for files by extension,
    - join-and-normalize helper for paths,
    - temporary file creation & safe read/cleanup utilities,
    - test environment setup/teardown helpers.
- `06_FilesystemTest/FilesystemTest.cpp`
  - Google Test cases validating extension extraction, directory creation (new and already‑existing), create/remove file behavior, file iteration, and cleanup semantics.

Requirements
- Windows 10/11
- Visual Studio 2022
- MSVC with C++17 support (ISO C++17)
- Google Test for the test project

Notes
- The examples emphasize deterministic cleanup and minimal side effects; keep those practices when adapting the utilities.
- Add license information as needed (e.g., MIT).