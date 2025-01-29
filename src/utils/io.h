#pragma once
#include <fstream>
#include <vector>

namespace blacklight
{
    std::vector<char> readShaderFile(const std::string& filename);
}