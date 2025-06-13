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

        [[nodiscard]] float3 ToWorldPoint(float3 p) const;
        [[nodiscard]] float3 ToLocalPoint(const float3 &worldPoint) const;

        [[nodiscard]] std::tuple<float3, float3, float3> GetInverseBasisVectors() const;

        [[nodiscard]] std::tuple<float3, float3, float3> GetBasisVectors() const;

        static float3 TransformVector(const float3 &ihat, const float3 &jhat, const float3 &khat, const float3 &v);
        [[nodiscard]] float3 scaleVector(float3 p) const;

        void update();

        Transform();
    };
}

#endif //TRANSFORM_HPP
