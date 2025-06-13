#include "../include/transform.hpp"

#include <complex>

#include "../dependencies/raylib/headers/raylib.h"

namespace rast {
    float3 Transform::ToWorldPoint(const float3 p) const {
        auto [ihat, jhat, khat] = GetBasisVectors();
        return TransformVector(ihat, jhat, khat, scaleVector(p)) + position;
    }

    float3 Transform::ToLocalPoint(const float3 &worldPoint) const {
        auto [ihat, jhat, khat] = GetInverseBasisVectors();
        return TransformVector(ihat, jhat, khat, worldPoint - position);
    }

    std::tuple<float3, float3, float3> Transform::GetInverseBasisVectors() const {
        const float3 ihat_yaw = {std::cos(-yaw), 0, std::sin(-yaw)};
        constexpr float3 jhat_yaw = {0, 1, 0};
        const float3 khat_yaw = {-std::sin(-yaw), 0, std::cos(-yaw)};

        constexpr float3 ihat_pitch = {1, 0, 0};
        const float3 jhat_pitch = {0, std::cos(-pitch), -std::sin(-pitch)};
        const float3 khat_pitch = {0, std::sin(-pitch), std::cos(-pitch)};

        float3 ihat = TransformVector(ihat_pitch, jhat_pitch, khat_pitch, ihat_yaw);
        float3 jhat = TransformVector(ihat_pitch, jhat_pitch, khat_pitch, jhat_yaw);
        float3 khat = TransformVector(ihat_pitch, jhat_pitch, khat_pitch, khat_yaw);

        return {ihat, jhat, khat};
    }

    std::tuple<float3, float3, float3> Transform::GetBasisVectors() const {
        const float3 ihat_yaw = {std::cos(yaw), 0, std::sin(yaw)};
        constexpr float3 jhat_yaw = {0, 1, 0};
        const float3 khat_yaw = {-std::sin(yaw), 0, std::cos(yaw)};

        constexpr float3 ihat_pitch = {1, 0, 0};
        const float3 jhat_pitch = {0, std::cos(pitch), -std::sin(pitch)};
        const float3 khat_pitch = {0, std::sin(pitch), std::cos(pitch)};

        float3 ihat = TransformVector(ihat_yaw, jhat_yaw, khat_yaw, ihat_pitch);
        float3 jhat = TransformVector(ihat_yaw, jhat_yaw, khat_yaw, jhat_pitch);
        float3 khat = TransformVector(ihat_yaw, jhat_yaw, khat_yaw, khat_pitch);

        return {ihat, jhat, khat};
    }

    float3 Transform::TransformVector(const float3 &ihat, const float3 &jhat, const float3 &khat, const float3 &v) {
        return v.x * ihat + v.y * jhat + v.z * khat;
    }

    float3 Transform::scaleVector(const float3 p) const {
        return {p.x * scale.x, p.y * scale.y, p.z * scale.z};
    }

    Transform::Transform() {
        yaw = 0;
        pitch = 0;
        position = {0, 0, 0};
        scale = {1, 1, 1};
    }
}
