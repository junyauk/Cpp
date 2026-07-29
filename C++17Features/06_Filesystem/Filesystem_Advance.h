#pragma once
#include <filesystem>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

namespace FILESYSTEM_Advance
{
	class Filesystem_Advance
	{
	public:
		// Helper method to create a temporary directory structure for testing
		void setupTestEnvironment(const fs::path& root) const;
		// Helper method to clean up the temporary directory structure
		void cleanupTestEnvironment(const fs::path& root) const;

		Filesystem_Advance() = default;
		~Filesystem_Advance();

		// 1. Application: Recursive Traversal
		// Recursively searches for files with a specific extension (.txt)
		std::vector<fs::path> findFilesRecursively(const fs::path& root, const std::string& extension) const;

		// 2. Application: Path Manipulation and Normalization
		// Joins a path and then normalizes it.
		fs::path joinAndNormalize(const fs::path& base, const fs::path& relative) const;

		// 3. Application: Temporary File Management
		// Creates a temporary file, writes to it, and ensures safe cleanup.
		std::string createAndReadTempFile() const;
	};

}

