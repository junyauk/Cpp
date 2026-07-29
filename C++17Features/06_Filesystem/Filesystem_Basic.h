#pragma once
#include <filesystem>
#include <string>
#include <vector>
#include <optional>

namespace FILESYSTEM_Basic
{
	class Filesystem_Basic
	{
	private:
		// Base directory for all temporary file operations
		std::filesystem::path m_basePath;
	public:
		// Constructor initializes the base path to a temporary directory
		Filesystem_Basic(const std::string& baseDirName);
		~Filesystem_Basic();

		// Cleans up the base directory and its contents
		void cleanup();

		// 1. Path Manipulation: Combines a path and returns its extension
		// Returns the extension of the combined path (basePath / subDir / filename).
		std::string getExtension(const std::string& subDir, const std::string& filename) const;

		// 2. Existence Check and Directory Creation
		// Creates a directory relative to the base path and returns true if successful or if it already exists.
		bool createDir(const std::string& relativePath);

		// 3. File Size and Removal
		// Creates a dummy file with content, gets its size, and then removes it.
		// Returns the size of the created file if successful.
		std::optional<uintmax_t> createAndRemoveFile(const std::string& filename, const std::string& content);

		// 4. Directory Iteration (Basic)
		// Returns a vector of filenames (not directories) found directly inside the base path.
		std::vector<std::string> listFilesInBaseDir() const;
	};
}

