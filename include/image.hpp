#pragma once
#include <string>
#include "../include/rendertarget.hpp"

namespace rast {
    void WriteImageToFile(const RenderTarget& image, const std::string& name);
}