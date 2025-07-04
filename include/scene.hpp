#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "model.hpp"
#include "rendertarget.hpp"
#include "camera.hpp"

class Scene {
public:
    std::vector<rast::Model> models;
    rast::Camera camera;

    void addModel(const rast::Model &model);

    void update(RenderTarget &target, float deltaTime);

    explicit Scene(const std::vector<rast::Model> &models);
    Scene();
private:
    void handleInput(const RenderTarget &target, float deltaTime);
};

#endif //SCENE_HPP
