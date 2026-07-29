#include "pch.h"
#include "Filesystem_Advance.h"
#include <random>

namespace FILESYSTEM_Advance
{
	// Helper method to create a temporary directory structure for testing
	void Filesystem_Advance::setupTestEnvironment(const fs::path& root) const
	{
		// Create the root directory
		fs::create_directories(root);

		// Create directories
		fs::create_directory(root / "dir1");
		fs::create_directories(root / "dir2" / "subdirA");

		// Create files
		std::ofstream(root / "fileA.txt") << "contentA";
		std::ofstream(root / "dir1" / "fileB.txt") << "contentB";
		std::ofstream(root / "dir1" / "fileC.txt") << "contentC";
		std::ofstream(root / "dir2" / "subdirA" / "fileD.txt") << "contentD";
	}
	// Helper method to clean up the temporary directory structure
	void Filesystem_Advance::cleanupTestEnvironment(const fs::path& root) const
	{
		if (fs::exists(root))
		{
			// std::filesystem::remove_all removes the directory and all its contents
			fs::remove_all(root);
		}
	}

	Filesystem_Advance::~Filesystem_Advance()
	{
		// No global cleanup needed, as the tests manage their own temporary scope
	}

	// 1. Application: Recursive Traversal
	// Recursively searches for files with a specific extension (.txt)
	std::vector<fs::path> Filesystem_Advance::findFilesRecursively(const fs::path& root, const std::string& extension) const
	{
		std::vector<fs::path> found_paths;

		// Use recursive_directory_iterator to traverse all subdirectories
		for (const auto& entry : fs::recursive_directory_iterator(root))
		{
			if (entry.is_regular_file() && entry.path().extension() == extension)
			{
				// Store the path relative to the root for testing clarity
				found_paths.push_back(fs::relative(entry.path(), root));
			}
		}
		return found_paths;
	}

	// 2. Application: Path Manipulation and Normalization
	// Joins a path and then normalizes it.
	fs::path Filesystem_Advance::joinAndNormalize(const fs::path& base, const fs::path& relative) const
	{
		// Path concatenation using the '/' operator (since C++17)
		fs::path combined = base / relative;

		// Normalization: Removes dot elements (./, ../) and resolves redundant separators (//).
		// On Linux, it often resolves to a canonical path but without following symlinks unless explicitly asked.
		return fs::weakly_canonical(combined);
		// Note: fs::weakly_canonical is used over fs::canonical to avoid throwing if path doesn't fully exist.
	}

	// 3. Application: Temporary File Management
	// Creates a temporary file, writes to it, and ensures safe cleanup.
	std::string Filesystem_Advance::createAndReadTempFile() const
	{
		// --- C++17 Compatible Unique Path Generation ---

		// 1. Get the system clock time (for a base unique seed)
		auto now = std::chrono::high_resolution_clock::now();
		auto seed = now.time_since_epoch().count();

		// 2. Use a random number generator
		std::mt19937_64 generator(static_cast<unsigned long long>(seed));
		std::uniform_int_distribution<unsigned long long> distribution;

		// 3. Construct a unique string using the random number
		std::stringstream unique_id;
		unique_id << std::hex << distribution(generator);

		// Construct the full temporary path
		fs::path temp_dir = fs::temp_directory_path();
		// Combine temporary directory path with the unique filename
		fs::path temp_path = temp_dir / ("temp_file_" + unique_id.str() + ".tmp");

		std::string content = "Temporary content for reading.";
		std::string read_content;

		try
		{
			// 2. Create and write to the temporary file
			std::ofstream ofs(temp_path);
			if (ofs) ofs << content;
			ofs.close();

			// 3. Read the content back
			std::ifstream ifs(temp_path);
			if (ifs)
			{
				std::stringstream buffer;
				buffer << ifs.rdbuf();
				read_content = buffer.str();
			}
		}
		catch (const fs::filesystem_error& e)
		{
			return "Filesystem Error: " + std::string{ e.what() };
		}

		// 4. Ensure cleanup
		if (fs::exists(temp_path))
		{
			fs::remove(temp_path);
		}

		return read_content;
	}
}

