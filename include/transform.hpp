#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <tuple>
#include <tuple>
#include "math.hpp"

namespace rast {
    class Transform {
    public:
        float yaw;
        float pitch;
        float3 position;
        float3 scale;

        float3 ToWorldPoint(float3 p) const;
        float3 ToLocalPoint(float3 worldPoint) const;

        std::tuple<float3, float3, float3> GetInverseBasisVectors() const;

        std::tuple<float3, float3, float3> GetBasisVectors() const;

        static float3 TransformVector(float3 ihat, float3 jhat, float3 khat, float3 v);
        float3 scaleVector(float3 p) const;

        void update();

        Transform();
    };
}

#endif //TRANSFORM_HPP
