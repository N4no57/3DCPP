#include "../include/model.hpp"

namespace rast {
    Model::Model(std::vector<float3> points, std::vector<Pixel> cols) : points(points), triangleCols(cols) {
        cashedScreenPoints.reserve(this->points.size());
        needsUpdate = true;
    }
}