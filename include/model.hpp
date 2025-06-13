#ifndef MODEL_HPP
#define MODEL_HPP

#include "math.hpp"
#include "transform.hpp"
#include "util.hpp"
#include <vector>

namespace rast {
    class Model {
    public:
        Model(std::vector<float3> points, std::vector<Pixel> cols);

        Transform transform;
        std::vector<float3> points;
        std::vector<Pixel> triangleCols;
        std::vector<float3> cashedScreenPoints;
        bool needsUpdate;
    };
}

#endif //MODEL_HPP
