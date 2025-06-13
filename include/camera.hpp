#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "transform.hpp"

namespace rast {
    class Camera {
    public:
        float fov;
        rast::Transform transform;



        Camera();
        Camera(float fov, rast::Transform transform);
    };
}

#endif //CAMERA_HPP
