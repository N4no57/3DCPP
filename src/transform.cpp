#include "../include/transform.hpp"

#include <complex>

#include "../dependencies/raylib/headers/raylib.h"

namespace rast {
    float3 Transform::ToWorldPoint(float3 p) const {
        auto [ihat, jhat, khat] = GetBasisVectors();
        return TransformVector(ihat, jhat, khat, scaleVector(p)) + position;
    }

    float3 Transform::ToLocalPoint(float3 worldPoint) const {
        auto [ihat, jhat, khat] = GetInverseBasisVectors();
        return TransformVector(ihat, jhat, khat, worldPoint - position);
    }

    std::tuple<float3, float3, float3> Transform::GetInverseBasisVectors() const {
        float3 ihat_yaw = {std::cos(-yaw), 0, std::sin(-yaw)};
        float3 jhat_yaw = {0, 1, 0};
        float3 khat_yaw = {-std::sin(-yaw), 0, std::cos(-yaw)};

        float3 ihat_pitch = {1, 0, 0};
        float3 jhat_pitch = {0, std::cos(-pitch), -std::sin(-pitch)};
        float3 khat_pitch = {0, std::sin(-pitch), std::cos(-pitch)};

        float3 ihat = TransformVector(ihat_pitch, jhat_pitch, khat_pitch, ihat_yaw);
        float3 jhat = TransformVector(ihat_pitch, jhat_pitch, khat_pitch, jhat_yaw);
        float3 khat = TransformVector(ihat_pitch, jhat_pitch, khat_pitch, khat_yaw);

        return {ihat, jhat, khat};
    }

    std::tuple<float3, float3, float3> Transform::GetBasisVectors() const {
        float3 ihat_yaw = {std::cos(yaw), 0, std::sin(yaw)};
        float3 jhat_yaw = {0, 1, 0};
        float3 khat_yaw = {-std::sin(yaw), 0, std::cos(yaw)};

        float3 ihat_pitch = {1, 0, 0};
        float3 jhat_pitch = {0, std::cos(pitch), -std::sin(pitch)};
        float3 khat_pitch = {0, std::sin(pitch), std::cos(pitch)};

        float3 ihat = TransformVector(ihat_yaw, jhat_yaw, khat_yaw, ihat_pitch);
        float3 jhat = TransformVector(ihat_yaw, jhat_yaw, khat_yaw, jhat_pitch);
        float3 khat = TransformVector(ihat_yaw, jhat_yaw, khat_yaw, khat_pitch);

        return {ihat, jhat, khat};
    }

    float3 Transform::TransformVector(float3 ihat, float3 jhat, float3 khat, float3 v) {
        float3 val = v.x * ihat + v.y * jhat + v.z * khat;
        return val;
    }

    float3 Transform::scaleVector(float3 p) const {
        return {p.x * scale.x, p.y * scale.y, p.z * scale.z};
    }

    Transform::Transform() {
        yaw = 0;
        pitch = 0;
        position = {0, 0, 0};
        scale = {1, 1, 1};
    }
}
