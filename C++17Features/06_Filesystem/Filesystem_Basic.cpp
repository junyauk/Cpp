#include "pch.h"
#include "framework.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "Filesystem_Basic.h"

namespace fs = std::filesystem; // Alias for convenience

namespace FILESYSTEM_Basic
{
	Filesystem_Basic::Filesystem_Basic(const std::string& baseDirName)
	{
		// 1. Determine a safe, system-dependent temporary path
		fs::path tempPath = fs::temp_directory_path();
		m_basePath = tempPath / baseDirName;

		// Ensure the directory exists (create it if it doesn't)
		fs::create_directories(m_basePath);
	}
	Filesystem_Basic::~Filesystem_Basic()
	{
		// Cleanup on destruction
		cleanup();
	}

	void Filesystem_Basic::cleanup()
	{
		// Remove the base directory and all its contents recursively
		if (fs::exists(m_basePath))
		{
			fs::remove_all(m_basePath);
		}
	}

	// 1. Path Manipulation
	std::string Filesystem_Basic::getExtension(const std::string& subDir, const std::string& filename) const
	{
		// Use the path operator/ to safely combine paths
		fs::path fullPath = m_basePath / subDir / filename;
		// Use extension() method and convert to string
		return fullPath.extension().string();
	}

	// 2. Existence Check and Directory Creation
	bool Filesystem_Basic::createDir(const std::string& relativePath)
	{
		fs::path dirPath = m_basePath / relativePath;

		if (fs::exists(dirPath))
		{
			return true;	// Directory already exists, return true
		}
		// Create the directory. Returns true on success.
		return fs::create_directory(dirPath);
	}

	// 3. File Size and Removal
	std::optional<uintmax_t> Filesystem_Basic::createAndRemoveFile(const std::string& filename, const std::string& content)
	{
		auto filePath = m_basePath / filename;

		// Create a dummy file
		std::ofstream ofs(filePath);
		if (!ofs) return std::nullopt;	// Failed to open/create
		ofs << content;
		ofs.close();

		std::optional<uintmax_t> size = std::nullopt;

		// Get file size
		if (fs::exists(filePath))
		{
			try
			{
				size = fs::file_size(filePath);
			}
			catch (const fs::filesystem_error& e)
			{
				// Handle size check error
				std::cerr << "Filesystem error getting size: " << e.what() << std::endl;
			}
		}

		// Remove the file
		// fs::remove returns true if a file/dir was successfully removed
		if (fs::remove(filePath))
		{
			return size;	// Return the size if removal was successful
		}
		return std::nullopt;// Removal failed
	}

	// 4. Directory Iteration (Basic)
	std::vector<std::string> Filesystem_Basic::listFilesInBaseDir() const
	{
		std::vector<std::string> files;

		// Iterate over the entries in the base directory
		for (const auto& entry : fs::directory_iterator(m_basePath))
		{
			// Check if the entry is a regular file
			if (fs::is_regular_file(entry.status()))
			{
				// Get the filename part of the path and store it
				files.push_back(entry.path().filename().string());
			}
		}
		return files;
	}
}
