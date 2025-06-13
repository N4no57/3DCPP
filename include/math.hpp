#pragma once

namespace rast {
    struct float2 {
        float x{}, y{};

        float dot(float2 A) const;
        float2 perpendicular() const;
    };

    struct float3
    {
        float x{}, y{}, z{};

        float r = x;
        float g = y;
        float b = z;

        float dot(float3 A) const;
        float magnitude() const;
        float3 normalize();
    };

    struct int3 {
        int x{}, y{}, z{};

    };

    float toRadians(float degrees);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// float2 functions
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float2 operator+(const float2& lhs, const float2& rhs);
    void operator+=(float2& lhs, const float2& rhs);
    float2 operator-(const float2& lhs, const float2& rhs);
    float2 operator*(const float2& lhs, const float& rhs);
    float2 operator/(const float2& lhs, const float& rhs);



    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// float3 functions
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float3 operator+(const float3& lhs, const float3& rhs);
    float3 operator-(const float3 &lhs, const float3 &rhs);
    float3 operator*(const float& lhs, const float3& rhs);
    float3 operator*(const float3& lhs, const float& rhs);
    float3 operator/(const float& lhs, const float3& rhs);
    void operator+=(float3& lhs, const float3& rhs);

    float dot(const float3& lhs, const float3& rhs);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// triangle functions
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool pointInTriangle(float2 a, float2 b, float2 c, float2 p, float3& weights);
    float signedTriangleArea(float2 a, float2 b, float2 c);
    float orient2D(float2 a, float2 b, float2 c);
    float3 computeBarycentrics(float a, float b, float c, float area, float invArea);
}