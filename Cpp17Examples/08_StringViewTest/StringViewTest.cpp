#include "pch.h"
#include <gtest/gtest.h>
#include "..\08_StringView\StringViewExamples.h"
#include "..\08_StringView\RemovePrefixSuffix.h"

using namespace StringViewExamples;

TEST(StringViewTest, SubString)
{
	std::string text = "Hello, World";
	auto sub = GetSubstr(text, 0, 5);
	EXPECT_EQ(sub, "Hello");
}

TEST(StringViewTest, Contains)
{
	EXPECT_TRUE(Contains("abcdef", "cd"));
	EXPECT_FALSE(Contains("abcef", "gh"));
}

TEST(StringViewTest, SplitWords)
{
	std::string text = "one tweo three";
	auto result = SplitWords(text);
	ASSERT_EQ(result.size(), 3);
	EXPECT_EQ(result[0], "one");
	EXPECT_EQ(result[1], "tweo");
	EXPECT_EQ(result[2], "three");

	auto words = SplitWords("This is a test");
	ASSERT_EQ(words.size(), 4);
	EXPECT_EQ(words[0], "This");
	EXPECT_EQ(words[1], "is");
	EXPECT_EQ(words[2], "a");
	EXPECT_EQ(words[3], "test");
	words = SplitWords("  Leading and trailing spaces  ");
	ASSERT_EQ(words.size(), 4);
	EXPECT_EQ(words[0], "Leading");
	EXPECT_EQ(words[1], "and");
	EXPECT_EQ(words[2], "trailing");
	EXPECT_EQ(words[3], "spaces");
	words = SplitWords("");
	ASSERT_TRUE(words.empty());
}

TEST(StringViewTest, SplitWordsWithExtraSpaces)
{
	std::string_view text = "   alpha   beta gamma   ";
	auto words = SplitWords(text);

	EXPECT_EQ(words.size(), 3u);
}

TEST(StringViewTest, ExtractFileName)
{
	EXPECT_EQ(getFileName("/usr/local/bin/test.txt"), "test");
	EXPECT_EQ(getFileName("C:\\Windows\\system32\\kernel32.dll"), "kernel32");
	EXPECT_EQ(getFileName("no_extension"), "no_extension");
}

TEST(StringViewTest, ExtractExtension)
{
	EXPECT_EQ(getExtension("/usr/local/bin/test.txt"), "txt");
	EXPECT_EQ(getExtension("archive.tar.gz"), "gz");
	EXPECT_EQ(getExtension("no_extension"), "");
}
TEST(StringViewTest, ExtractExtensionNoDot)
{
	EXPECT_EQ(getExtension("filename"), "");
	EXPECT_EQ(getExtension("anotherfile"), "");
}
TEST(StringViewTest, ExtractExtensionDotAtEnd)
{
	EXPECT_EQ(getExtension("filename."), "");
	EXPECT_EQ(getExtension("anotherfile."), "");
}
TEST(StringViewTest, ExtractFileNameNoPath)
{
	EXPECT_EQ(getFileName("simplefile.txt"), "simplefile");
	EXPECT_EQ(getFileName("anotherfile"), "anotherfile");
}
TEST(StringViewTest, ExtractFileNameWithDots)
{
	EXPECT_EQ(getFileName("/path.to/some.file.name.txt"), "some.file.name");
	EXPECT_EQ(getFileName("C:\\path.to\\another.file.name"), "another.file");
}
TEST(StringViewTest, ExtractFileNameEdgeCases)
{
	EXPECT_EQ(getFileName(""), "");
	EXPECT_EQ(getFileName("/"), "");
	EXPECT_EQ(getFileName("C:\\"), "");
	EXPECT_EQ(getFileName("/path/to/directory/"), ""); // Directory path
	EXPECT_EQ(getFileName("C:\\path\\to\\directory\\"), ""); // Directory path
}
TEST(StringViewTest, ExtractExtensionEdgeCases)
{
	EXPECT_EQ(getExtension(""), "");
	EXPECT_EQ(getExtension("."), "");
	EXPECT_EQ(getExtension(".."), "");
	EXPECT_EQ(getExtension("file."), "");
	EXPECT_EQ(getExtension("file.name."), "");
}
TEST(StringViewTest, ExtractFileNameNoSuffix)
{
	EXPECT_EQ(getFileName("/path/to/file"), "file");
	EXPECT_EQ(getFileName("C:\\path\\to\\file"), "file");
}
TEST(StringViewTest, ExtractExtensionMultipleDots)
{
	EXPECT_EQ(getExtension("file.name.with.many.dots.ext"), "ext");
	EXPECT_EQ(getExtension("another.file.name.with.many.dots"), "dots");
}
TEST(StringViewTest, ExtractExtensionOnlyDots)
{
	EXPECT_EQ(getExtension("..."), "");
	EXPECT_EQ(getExtension("file..."), "");
	EXPECT_EQ(getExtension("file.name..."), "");
}
TEST(StringViewTest, ExtractFileNameSpecialCharacters)
{
	EXPECT_EQ(getFileName("/path/to/fi!le@#$.txt"), "fi!le@#$");
	EXPECT_EQ(getFileName("C:\\path\\to\\fi%le^&*.dll"), "fi%le^&*");
}
TEST(StringViewTest, ExtractExtensionSpecialCharacters)
{
	EXPECT_EQ(getExtension("fi!le@#$.txt"), "txt");
	EXPECT_EQ(getExtension("fi%le^&*.dll"), "dll");
}
TEST(StringViewTest, ExtractFileNameUnicode)
{
	EXPECT_EQ(getFileName("/path/to/ï∂åè.txt"), "ï∂åè");
	EXPECT_EQ(getFileName("C:\\òHåa\\ìû\\ï∂åè.dll"), "ï∂åè");
}
TEST(StringViewTest, ExtractExtensionUnicode)
{
	EXPECT_EQ(getExtension("ï∂åè.txt"), "txt");
	EXPECT_EQ(getExtension("ï∂åè.dll"), "dll");
}
TEST(StringViewTest, ExtractFileNameLongPath)
{
	std::string longPath(300, 'a'); // Create a long path of 300 'a' characters
	longPath += "/file.txt";
	EXPECT_EQ(getFileName(longPath), "file");
}
TEST(StringViewTest, ExtractExtensionLongFileName)
{
	std::string longFileName(300, 'b'); // Create a long file name of 300 'b' characters
	longFileName += ".ext";
	EXPECT_EQ(getExtension(longFileName), "ext");
}
TEST(StringViewTest, ExtractFileNameNoPathWithDots)
{
	EXPECT_EQ(getFileName("file.name.with.dots.txt"), "file.name.with.dots");
	EXPECT_EQ(getFileName("another.file.name.with.dots"), "another.file.name.with");
}
TEST(StringViewTest, ExtractExtensionNoPathWithDots)
{
	EXPECT_EQ(getExtension("file.name.with.dots.txt"), "txt");
	EXPECT_EQ(getExtension("another.file.name.with.dots"), "dots");
}
TEST(StringViewTest, ExtractFileNameMixedSeparators)
{
	EXPECT_EQ(getFileName("C:/path\\to/mixed\\separators/file.txt"), "file");
	EXPECT_EQ(getFileName("/unix\\style/mixed/separators/file.txt"), "file");
}
