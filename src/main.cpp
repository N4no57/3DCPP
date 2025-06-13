#include <utility>
#include <vector>
#include "../include/math.hpp"
#include "../include/util.hpp"
#include "../include/render.hpp"
#include "../include/scene.hpp"
#include "../include/objParser.hpp"
#include "../include/model.hpp"
#include "../include/rendertarget.hpp"

int toAspectRatio(int height) {
    int temp = height / 9;
    return temp * 16;
}

//float3(0.992156862745,0.862745098039, 0.341176470588)

rast::Model generateModel(std::string objFile) {
    const auto modelPoints = rast::loadObjectFile(std::move(objFile));
    std::vector<rast::Pixel> triangleCols;
    triangleCols.resize(modelPoints.size() / 3);
    for (auto & triangleCol : triangleCols) {
        triangleCol = rast::randomColour();
    }

    const rast::Model model(modelPoints, triangleCols);
    return model;
}

void CreateTestImage()
{
    constexpr int height = 720;
    const int width = toAspectRatio(height);

    Scene scene;
    RenderTarget image(width, height);
    rast::Camera camera;
    scene.camera = camera;

    rast::Model suzanneModel = generateModel("../suzanne.obj");
    suzanneModel.transform.position = {0, 0.9, 5};
    scene.addModel(suzanneModel);

    rast::Model cube1 = generateModel("../cube.obj");

    cube1.transform.position = {-5, 0, 12};
    cube1.transform.yaw = rast::toRadians(30);
    scene.addModel(cube1);

    rast::Model cube2 = generateModel("../cube.obj");

    cube2.transform.position = {5, 0, 12};
    cube2.transform.yaw = rast::toRadians(-30);
    scene.addModel(cube2);

    rast::Model cube3 = generateModel("../cube.obj");

    cube3.transform.position = {6, 0, 8};
    cube3.transform.yaw = rast::toRadians(30);
    scene.addModel(cube3);

    rast::Model cube4 = generateModel("../cube.obj");
    cube4.transform.position = {-6, 0, 8};
    cube4.transform.yaw = rast::toRadians(-30);
    scene.addModel(cube4);

    rast::Model plane = generateModel("../plane.obj");
    plane.transform.position = {0, -1, 10};
    plane.transform.scale = {8, 1, 8};
    scene.addModel(plane);

    rast::run(scene, image);
}

int main()
{
    CreateTestImage();
    return 0;
}