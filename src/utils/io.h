#pragma once
#include <fstream>
#include <vector>

namespace blacklight
{
    std::vector<char> readFile(const std::string& filename);
}