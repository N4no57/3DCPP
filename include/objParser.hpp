#pragma once
#include <string>
#include <vector>
#include "math.hpp"

namespace rast {
    std::vector<float3> loadObjectFile(const std::string &filename);
}