#include "../include/math.hpp"
#include <cmath>
#include <stdexcept>

namespace rast {
    float float2::dot(float2 A) const {
        return A.x * this->x + A.y * this->y;
    }

    float2 float2::perpendicular() const {
        return float2(this->y, -this->x);
    }

    float float3::dot(float3 A) const {
        return A.x * this->x + A.y * this->y + A.z * this->z;
    }

    float float3::magnitude() const {
        return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }

    float3 float3::normalize() {
        float magnitude = this->magnitude();
        if (magnitude == 0.0f) {
            return float3(0.0f, 0.0f, 0.0f);
        }
        return { x / magnitude, y / magnitude, z / magnitude };
    }

    float toRadians(float degrees) {
        return degrees * (M_PI / 180.f);
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// float2 functions
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float2 operator+(const float2& lhs, const float2& rhs) {
        return float2(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    void operator+=(float2& lhs, const float2& rhs) {
        lhs = lhs + rhs;
    }

    float2 operator-(const float2& lhs, const float2& rhs) {
        return float2(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    float2 operator*(const float2& lhs, const float& rhs) {
        return { lhs.x * rhs, lhs.y * rhs };
    }

    float2 operator/(const float2& lhs, const float& rhs) {
        return { lhs.x / rhs, lhs.y / rhs };
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// float3 functions
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float3 operator+(const float3& lhs, const float3& rhs) {
        return float3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    }

    float3 operator-(const float3 &lhs, const float3 &rhs) {
        return float3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    }

    float3 operator*(const float& lhs, const float3& rhs) {
        return float3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
    }

    float3 operator*(const float3 &lhs, const float &rhs) {
        return float3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
    }

    float3 operator/(const float &lhs, const float3 &rhs) {
        return {lhs / rhs.x, lhs / rhs.y, lhs / rhs.z};
    }

    void operator+=(float3& lhs, const float3& rhs) {
        lhs = lhs + rhs;
    }

    float dot(const float3 &lhs, const float3 &rhs) {
        return lhs.dot(rhs);
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// triangle functions
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool pointInTriangle(float2 a, float2 b, float2 c, float2 p, float3& weights) {
        float areaABP = signedTriangleArea(a, b, p);
        float areaBCP = signedTriangleArea(b, c, p);
        float areaCAP = signedTriangleArea(c, a, p);
        bool inTri = areaABP >= 0 && areaBCP >= 0 && areaCAP >= 0;

        float totalArea = areaABP + areaBCP + areaCAP;
        float invAreaSum = 1 / totalArea;
        float weightA = areaBCP * invAreaSum;
        float weightB = areaCAP * invAreaSum;
        float weightC = areaABP * invAreaSum;
        weights = {weightA, weightB, weightC};

        return inTri && totalArea > 0;
    }

    float signedTriangleArea(float2 a, float2 b, float2 c) {
        float2 ac = c - a;
        float2 abPerp = ac.perpendicular();
        return ac.dot(abPerp) / 2;
    }

    float orient2D(float2 a, float2 b, float2 c) {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }

    float3 computeBarycentrics(float w0, float w1, float w2, float area, float invArea) {
        return {w0 * invArea, w1 * invArea, w2 * invArea};
    }
}
