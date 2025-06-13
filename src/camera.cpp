#include "../include/camera.hpp"

namespace rast {
    Camera::Camera() {
        fov = rast::toRadians(60);
        transform = rast::Transform();
    }
    Camera::Camera(const float fov, const rast::Transform &transform): fov(fov), transform(transform) {}
}
