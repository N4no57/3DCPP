#include "../include/util.hpp"
#include <random>

namespace rast {
    float2 randomFloat2(int min, int max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());

        std::uniform_real_distribution<float> distX(0.0f, min);
        std::uniform_real_distribution<float> distY(0.0f, max);

        return { distX(gen), distY(gen) };
    }

    Pixel randomColour() {
        Pixel colour;
        static std::random_device rd;
        static std::mt19937 gen(rd());

        std::uniform_int_distribution<uint8_t> dist(0, 255);

        colour.r = dist(gen);
        colour.g = dist(gen);
        colour.b = dist(gen);

        return colour;
    }
}