#pragma once
#include <string>
#include <vector>
#include "math.hpp"

namespace rast {
    std::vector<float3> loadObjectFile(std::string filename);
}