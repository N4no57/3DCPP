#include "../include/camera.hpp"

namespace rast {
    Camera::Camera() {
        fov = rast::toRadians(60);
        transform = rast::Transform();
    }

    Camera::Camera(float fov, rast::Transform transform): fov(fov), transform(transform) {}
}
