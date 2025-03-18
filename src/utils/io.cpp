#include "io.h"
#include <fstream>
#include <vector>

//Read a file
std::vector<char> blacklight::readFile(const std::string& filename)
{
	//get file stream
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	//check if file existe
	if (!file.is_open())
		throw std::runtime_error("failed to open file : " + filename);
	
	//get size and allocate buffer
	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	//read file
	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close()

	return buffer;
}
