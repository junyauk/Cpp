#pragma once
#include <string>
#include <vector>


namespace Ex05_ThreadPool_IO
{
	struct LogChunkContext
	{
		std::vector<unsigned char> buffer;
		size_t offset;
		size_t requested;
	};
}