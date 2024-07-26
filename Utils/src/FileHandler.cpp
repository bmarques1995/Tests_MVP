#include "FileHandler.hpp"
#include <fstream>

bool SampleRender::FileHandler::ReadTextFile(std::string_view path, std::string* content)
{
	bool loaded = false;
	std::ifstream fileStream;
	fileStream.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	try
	{
		fileStream.open(path.data(), std::ios::binary);
		loaded = true;
	}
	catch (...)
	{
		return loaded;
	}
	auto start = fileStream.tellg();
	fileStream.seekg(0, std::ios::end);
	uint64_t fsize = fileStream.tellg() - start;
	fileStream.seekg(0, std::ios::beg);
	char* buffer = new char[fsize + 1];
	buffer[fsize] = '\0';
	fileStream.read(buffer, fsize);
	*content = buffer;
	delete[] buffer;
	return loaded;
}

bool SampleRender::FileHandler::WriteTextFile(std::string_view path, std::string content)
{
	bool stored = false;
	std::ofstream fileStream;
	fileStream.exceptions(std::ofstream::badbit);
	try
	{
		fileStream.open(path.data(), std::ios::out | std::ios::binary);
		stored = true;
	}
	catch (...)
	{
		return stored;
	}
	fileStream << content;
	return stored;
}

bool SampleRender::FileHandler::ReadBinFile(std::string_view path, std::byte** content, size_t* fileSize)
{
	bool loaded = false;
	std::ifstream fileStream;
	fileStream.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	try
	{
		fileStream.open(path.data(), std::ios::binary);
		loaded = true;
	}
	catch (...)
	{
		return loaded;
	}
	auto start = fileStream.tellg();
	fileStream.seekg(0, std::ios::end);
	uint64_t fsize = fileStream.tellg() - start;
	*fileSize = fsize;
	fileStream.seekg(0, std::ios::beg);
	*content = new std::byte[fsize];
	fileStream.read(reinterpret_cast<char*>(*content), fsize);
	return loaded;
}

bool SampleRender::FileHandler::WriteBinFile(std::string_view path, std::byte* content, size_t dataSize)
{
	bool stored = false;
	std::ofstream fileStream;
	fileStream.exceptions(std::ofstream::badbit);
	try
	{
		fileStream.open(path.data(), std::ios::out | std::ios::binary);
		stored = true;
	}
	catch (...)
	{
		return stored;
	}
	fileStream.write(reinterpret_cast<char*>(content), dataSize);
	return stored;
}

bool SampleRender::FileHandler::FileExists(std::string_view path)
{
	bool loaded = false;
	std::ifstream fileStream;
	fileStream.exceptions(std::ifstream::failbit);
	try
	{
		fileStream.open(path.data(), std::ios::binary);
		loaded = true;
		fileStream.close();
	}
	catch (...)
	{
	}
	return loaded;
}
