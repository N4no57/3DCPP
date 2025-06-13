#pragma once
#include <cstdint>

#include "math.hpp"

namespace rast {
    struct Pixel {
        uint8_t r, g, b, a;

        Pixel() : r(0), g(0), b(0), a(255) {}
        Pixel(const uint8_t r, const uint8_t g, const uint8_t b) : r(r), g(g), b(b) {
            a = 255;
        }
    };

    float2 randomFloat2(int min, int max);
    Pixel randomColour();
}
