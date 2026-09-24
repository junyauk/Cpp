#pragma once
#include <Windows.h>
#include <string_view>
#include "scopedhandle.h"
#include "ilogprocessor.h"

namespace Ex05_ThreadPool_IO
{
	class ClassicLogProcessor : public ILogProcessor
	{
	public:
		ClassicLogProcessor()
			: m_buffer(std::make_unique<char[]>(BUFFER_SIZE))
		{}
		~ClassicLogProcessor() = default;

		ClassicLogProcessor(const ClassicLogProcessor&) = delete;
		ClassicLogProcessor(ClassicLogProcessor&&) = delete;
		ClassicLogProcessor& operator=(const ClassicLogProcessor&) = delete;
		ClassicLogProcessor& operator=(ClassicLogProcessor&&) = delete;

		LogAnalysisResult Process(const std::wstring& filePath) override
		{
			HANDLE hFile = CreateFileW(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
			if (hFile == INVALID_HANDLE_VALUE)
			{
				// Handle error
				return LogAnalysisResult{};
			}
			m_fileHandle.reset(hFile);

			LogAnalysisResult result;
			size_t leftoverSize = 0;

			auto startTime = std::chrono::high_resolution_clock::now();
			while (true)
			{
				// Read file in chunks and process
				// For simplicity, let's assume we read the entire file into memory
				// In a real-world scenario, you would read in chunks and process each chunk
				DWORD bytesRead = 0;
				if (!ReadFile(m_fileHandle.get(), m_buffer.get() + leftoverSize, BUFFER_SIZE - leftoverSize, &bytesRead, nullptr))
				{
					// Handle error
					break;
				}
				if (bytesRead == 0)
				{
					// End of file
					if (leftoverSize > 0)
					{
						// Process any leftover data
						std::string_view bufferView(m_buffer.get(), leftoverSize);
						ParseChunk(bufferView, result, true);
					}
					break;
				}

				// Create a string_view of the buffer to avoid copying
				std::string_view bufferView(m_buffer.get(), bytesRead + leftoverSize);
				size_t processedBytes = ParseChunk(bufferView, result);
				leftoverSize = bufferView.size() - processedBytes;
				// Move leftover bytes to the beginning of the buffer for the next read
				std::memmove(m_buffer.get(), m_buffer.get() + processedBytes, leftoverSize);
			}
			auto endTime = std::chrono::high_resolution_clock::now();
			result.processingTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

			return result;
		}

	private:
		size_t ParseChunk(const std::string_view& buffer, LogAnalysisResult& result, bool isEOF = false)
		{
			size_t lines = 0;
			size_t errors = 0;
			size_t offset = 0;
			while (offset < buffer.size())
			{
				size_t lf = buffer.find('\n', offset);
				if (lf == std::string_view::npos && !isEOF)
				{
					// incomplete line at the end of the buffer, will be processed in the next chunk
					break;
				}
				lines++;
				size_t lineEnd = (lf == std::string_view::npos) ? buffer.size() : lf;
				std::string_view line = buffer.substr(offset, lineEnd - offset);
				if (line.find("[ERROR]") != std::string_view::npos)
				{
					errors++;
				}
				// Move offset to the next line
				if (lf == std::string_view::npos)
				{
					// If we are at the end of the buffer and it's EOF, we process the last line
					offset = buffer.size();
				}
				else
				{
					// Move past the newline character
					offset = lf + 1;
				}
			}
			result.totalLines += lines;
			result.errorCounts += errors;
			result.totalBytes += offset;
			return offset; // Return the number of bytes processed
		}

		const static uint64_t BUFFER_SIZE = 1024 * 1024; // 1 MB buffer
		std::unique_ptr<char[]> m_buffer;
		ScopedHandle m_fileHandle;
	};
}
