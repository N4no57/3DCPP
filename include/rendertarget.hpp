#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP

#include "math.hpp"
#include "util.hpp"
#include "vector"

class RenderTarget {
public:
    RenderTarget(int w, int h);

    int getWidth() const;
    int getHeight() const;
    rast::float2 getSize() const;

    void clearScreen();

    std::vector<rast::Pixel> colourBuffer;
    std::vector<float> depthBuffer;

private:
    int width;
    int height;
    rast::float2 size;
    float farClipPlane;
};



#endif //RENDERTARGET_HPP
