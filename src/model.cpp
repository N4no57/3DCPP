#include <utility>
#include "../include/model.hpp"

namespace rast {
    Model::Model(std::vector<float3> points, std::vector<Pixel> cols) : points(std::move(points)), triangleCols(std::move(cols)) {
        cashedScreenPoints.reserve(this->points.size());
        needsUpdate = true;
    }
}