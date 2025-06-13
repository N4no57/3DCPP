#include "../include/scene.hpp"

#include <chrono>
#include <iostream>

#include "../include/math.hpp"
#include "../dependencies/raylib/headers/raylib.h"
#include <bits/stl_algo.h>

void needUpdate(std::vector<rast::Model> &models) {
    for (int i = 0; i < models.size(); i++) {
        models[i].needsUpdate = true;
    }
}

void Scene::addModel(rast::Model model) {
    models.push_back(model);
}

void Scene::handleInput(RenderTarget &target, float deltaTime) {
    float camSpeed = 1.5f;
    float camSensitivity = 2.f;

    rast::float2 mouseDelta = {GetMouseDelta().x, GetMouseDelta().y};
    mouseDelta = mouseDelta / target.getWidth() * camSensitivity;
    if (mouseDelta.x != 0 || mouseDelta.y != 0) {
     needUpdate(models);
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        camera.transform.pitch = std::clamp(camera.transform.pitch - mouseDelta.y,
            rast::toRadians(-85), rast::toRadians(85));
        camera.transform.yaw -= mouseDelta.x;
    }

    rast::float3 moveDelta = {0, 0, 0};
    auto [camRight, camUp, camFwd] = camera.transform.GetBasisVectors();

    if (IsKeyDown(KEY_W)) {
        moveDelta += camFwd;
        needUpdate(models);
    }
    if (IsKeyDown(KEY_S)) {
        moveDelta = moveDelta - camFwd;
        needUpdate(models);
    }
    if (IsKeyDown(KEY_A)) {
        moveDelta = moveDelta - camRight;
        needUpdate(models);
    }
    if (IsKeyDown(KEY_D)) {
        moveDelta += camRight;
        needUpdate(models);
    }
    if (IsKeyDown(KEY_SPACE)) {
        moveDelta += camUp;
    }
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        moveDelta = moveDelta - camUp;
    }

    camera.transform.position += moveDelta.normalize() * camSpeed * deltaTime;
}

void Scene::update(RenderTarget &target, float deltaTime) {
    target.clearScreen();

    models[0].transform.pitch += rast::toRadians(45) * deltaTime;
    models[0].needsUpdate = true;

    handleInput(target, deltaTime);
}

Scene::Scene(std::vector<rast::Model> models) : models(models) {}

Scene::Scene() = default;


