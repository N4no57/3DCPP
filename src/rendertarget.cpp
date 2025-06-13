#include "../include/rendertarget.hpp"
#include <chrono>
#include <iostream>

RenderTarget::RenderTarget(const int w, const int h) : width(w), height(h) {
    size = rast::float2(static_cast<float>(width), static_cast<float>(height));
    farClipPlane = 50.f;

    colourBuffer.resize(width * height);
    depthBuffer.resize(width * height, farClipPlane);
}

int RenderTarget::getWidth() const {
    return width;
}

int RenderTarget::getHeight() const {
    return height;
}

rast::float2 RenderTarget::getSize() const {
    return size;
}

void RenderTarget::clearScreen() {
    const auto start = std::chrono::high_resolution_clock::now();
    std::ranges::fill(colourBuffer, rast::Pixel(0, 0, 0));
    std::ranges::fill(depthBuffer, farClipPlane);
    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Clear Screen time: " << std::chrono::duration<float, std::milli>(end - start).count() << "ms\n";
}
