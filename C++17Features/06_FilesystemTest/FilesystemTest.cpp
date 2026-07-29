#include "pch.h"
#include <fstream>
#include <string>
#include <memory>
#include "..\06_Filesystem\Filesystem_Basic.h"

namespace fs = std::filesystem;

// Define the test fixture class
namespace FilesystemTest
{
    // Use a unique name for the temporary directory to avoid conflicts
    const std::string TEST_DIR_NAME = "C++17_FSTest_06";

    class FilesystemTest : public ::testing::Test
    {
    protected:
        // Use a pointer/unique_ptr to control construction/destruction explicitly 
        // to ensure cleanup() is called after each test.
        std::unique_ptr<FILESYSTEM_Basic::Filesystem_Basic> m_fs;
        fs::path m_basePath;

        void SetUp() override
        {
            // Initialize a new Filesystem_Basic object for each test
            m_fs = std::make_unique<FILESYSTEM_Basic::Filesystem_Basic>(TEST_DIR_NAME);

            // Reconstruct m_basePath manually for external checks
            m_basePath = fs::temp_directory_path() / TEST_DIR_NAME;

            // Ensure the base directory exists before tests start
            ASSERT_TRUE(fs::exists(m_basePath));
            ASSERT_TRUE(fs::is_directory(m_basePath));
        }

        void TearDown() override
        {
            // Cleanup is handled by the Filesystem_Basic destructor (m_fs->cleanup())
            // but we ensure it's called and the directory is gone.
            m_fs.reset();
            // Check that the cleanup worked
            ASSERT_FALSE(fs::exists(m_basePath));
        }

        // Helper to create a dummy file for testing iteration
        void createDummyFile(const std::string& filename)
        {
            std::ofstream ofs(m_basePath / filename);
            ofs << "dummy content";
        }
    };

    // Test Case 1: Path Manipulation
    TEST_F(FilesystemTest, GetExtension_ReturnsCorrectExtension)
    {
        // Combines base/subdir/file.ext and gets ".ext"
        std::string ext = m_fs->getExtension("sub_dir", "test_file.txt");
        ASSERT_EQ(".txt", ext);
    }

    TEST_F(FilesystemTest, GetExtension_ReturnsEmptyForNoExtension)
    {
        std::string ext = m_fs->getExtension("", "filename_without_ext");
        ASSERT_EQ("", ext);
    }

    // Test Case 2: Existence Check and Directory Creation
    TEST_F(FilesystemTest, CreateDir_NewDirectory)
    {
        // Try to create a new directory
        ASSERT_TRUE(m_fs->createDir("NewFolder"));

        // Verify creation using std::filesystem::exists
        ASSERT_TRUE(fs::exists(m_basePath / "NewFolder"));
        ASSERT_TRUE(fs::is_directory(m_basePath / "NewFolder"));
    }

    TEST_F(FilesystemTest, CreateDir_AlreadyExists)
    {
        // Create it first
        fs::create_directory(m_basePath / "ExistingFolder");

        // Try to create it again (should return true)
        ASSERT_TRUE(m_fs->createDir("ExistingFolder"));
        // No exception should be thrown
    }

    // Test Case 3: File Size and Removal
    TEST_F(FilesystemTest, CreateAndRemoveFile_Success)
    {
        const std::string content = "Hello Filesystem!";
        // The size should be the length of the string (17)
        uintmax_t expectedSize = content.length();

        // Create, get size, and remove
        auto resultSize = m_fs->createAndRemoveFile("removable.tmp", content);

        // Check if a size was returned (meaning creation and removal succeeded)
        ASSERT_TRUE(resultSize.has_value());
        ASSERT_EQ(expectedSize, resultSize.value());

        // Double-check that the file is actually gone
        ASSERT_FALSE(fs::exists(m_basePath / "removable.tmp"));
    }

    // Test Case 4: Directory Iteration
    TEST_F(FilesystemTest, ListFilesInBaseDir_ReturnsOnlyFiles)
    {
        // Setup: create some files and a directory
        createDummyFile("file_A.log");
        createDummyFile("file_B.log");
        fs::create_directory(m_basePath / "subDir_C");

        // List files
        std::vector<std::string> files = m_fs->listFilesInBaseDir();

        // Only 2 files should be found, not the directory
        ASSERT_EQ(2, files.size());

        // Check contents
        std::sort(files.begin(), files.end());
        ASSERT_EQ("file_A.log", files[0]);
        ASSERT_EQ("file_B.log", files[1]);
    }
}
