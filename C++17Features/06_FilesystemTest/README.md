# 06_FilesystemTest

This test project contains unit tests (Google Test) for the `06_Filesystem` utilities. Tests validate path manipulation, directory and file operations, recursive behavior expectations, and deterministic cleanup semantics.

Contents
- `FilesystemTest.cpp` — Test fixture and cases covering:
  - Construction and teardown of a temporary base directory used by `Filesystem_Basic`.
  - `GetExtension` behavior for files with and without extensions.
  - `createDir` idempotency and directory existence checks.
  - `createAndRemoveFile` verifying created file size and successful removal.
  - `listFilesInBaseDir` ensuring only regular files are returned (directories excluded).
  - Test helpers to create dummy files and reconstruct expected temp paths for verification.

Requirements
- Visual Studio 2022
- MSVC with C++17 support (ISO C++17)
- Google Test configured in the solution (vcpkg, submodule, or vendor)

Build
1. Open the solution in Visual Studio 2022.
2. Ensure the test project and implementation target ISO C++17 (Project Properties → C/C++ → Language → C++ Language Standard → `ISO C++17`).
3. Build the solution (Right-click solution → Build Solution).

Run tests
- In Visual Studio: Open __Test Explorer__ (Test → Test Explorer) and run all or selected tests.
- Or run the produced test executable directly:
  Example: `.\06_FilesystemTest\Debug\06_FilesystemTest.exe`

Expected behavior summary
- Temporary base directory is created under the system temporary path and removed during teardown.
- `GetExtension` returns the correct extension string (including leading '.') or an empty string when none exists.
- `createDir` returns true for new directories and for directories that already exist.
- `createAndRemoveFile` returns the size of the created file and removes it from disk.
- `listFilesInBaseDir` returns only regular file names and excludes directories.

Notes
- Tests use a unique temporary directory name to avoid interfering with other data.
- If tests fail, verify permissions for the system temporary directory and that `std::filesystem` operations are supported on your platform.
- Add license or contributing references in the parent project README as needed.