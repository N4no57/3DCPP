#include "../include/render.hpp"
#include "../include/image.hpp"
#include "../dependencies/raylib/headers/raylib.h"
#include "../include/camera.hpp"
#include <format>
#include <iostream>
#include <chrono>
#include <cmath>

namespace rast {
    int ceilInt(float x) {
        int intPart = static_cast<int>(x);
        if (x > static_cast<float>(intPart)) {intPart++;}
        return intPart;
    }

    float3 vertexToScreen(float3 vertex, Transform transform, rast::Camera &camera, float2 screenSize) {
        float3 vertex_world = transform.ToWorldPoint(vertex);
        float3 vertex_view = camera.transform.ToLocalPoint(vertex_world);

        float screenHeight_world = std::tan(camera.fov / 2) * 2;
        float pixelsPerWorldUnit = screenSize.y / screenHeight_world / vertex_view.z;

        float2 pixelOffset = float2(vertex_view.x, vertex_view.y) * pixelsPerWorldUnit;
        float2 vertex_screen = screenSize / 2 + pixelOffset;
        return {vertex_screen.x, vertex_screen.y, vertex_view.z};
    }

    void render(RenderTarget &image, std::vector<Model> &models, rast::Camera &camera) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < models.size(); i++) {
            if (models[i].needsUpdate) {
                models[i].cashedScreenPoints.resize(models[i].points.size());
                for (int v = 0; v < models[i].points.size(); ++v) {
                    models[i].cashedScreenPoints[v] = vertexToScreen(
                        models[i].points[v],
                        models[i].transform,
                        camera,
                        image.getSize()
                    );
                }
                models[i].needsUpdate = false;
            }

            for (int j = 0; j < models[i].points.size(); j+=3) {
                float3 a = models[i].cashedScreenPoints[j+0];
                float3 b = models[i].cashedScreenPoints[j+1];
                float3 c = models[i].cashedScreenPoints[j+2];
                if (a.z <= 0 || b.z <= 0 || c.z <= 0) continue;

                float minX = std::min({a.x, b.x, c.x});
                float minY = std::min({a.y, b.y, c.y});
                float maxX = std::max({a.x, b.x, c.x});
                float maxY = std::max({a.y, b.y, c.y});

                int blockStartX = std::clamp(static_cast<int>(minX), 0, image.getWidth() - 1);
                int blockStartY = std::clamp(static_cast<int>(minY), 0, image.getHeight() - 1);
                int blockEndX = std::clamp(ceilInt(maxX), 0, image.getWidth() - 1);
                int blockEndY = std::clamp(ceilInt(maxY), 0, image.getHeight() - 1);

                // Precompute edge function deltas
                float A01 = a.y - b.y, B01 = b.x - a.x;
                float A12 = b.y - c.y, B12 = c.x - b.x;
                float A20 = c.y - a.y, B20 = a.x - c.x;

                float area = orient2D({a.x, a.y}, {b.x, b.y}, {c.x, c.y});
                if (area >= 0) continue; // Degenerate triangle
                float invArea = 1.0f / area;

                float w0_row = orient2D({b.x, b.y}, {c.x, c.y}, float2(blockStartX, blockStartY));
                float w1_row = orient2D({c.x, c.y}, {a.x, a.y}, float2(blockStartX, blockStartY));
                float w2_row = orient2D({a.x, a.y}, {b.x, b.y}, float2(blockStartX, blockStartY));

                float3 depths = {a.z, b.z, c.z};

                for (int y = blockStartY; y < blockEndY; y++) {
                    float w0 = w0_row, w1 = w1_row, w2 = w2_row;
                    int flippedY = (image.getHeight() - 1) - y;
                    int rowOffset = flippedY * image.getWidth();

                    Pixel* colorPtr = &image.colourBuffer[rowOffset + blockStartX];
                    float* depthPtr = &image.depthBuffer[rowOffset + blockStartX];
                    for (int x = blockStartX; x < blockEndX; x++) {
                        if (w0 <= 0 && w1 <= 0 && w2 <= 0) {
                            float3 weights = computeBarycentrics(w0, w1, w2, area, invArea);
                            float depth = 1 / dot(1 / depths, weights);
                            if (depth < *depthPtr) {
                                *colorPtr = models[i].triangleCols[j / 3];
                                *depthPtr = depth;
                            }
                        }
                        w0 += A12; w1 += A20; w2 += A01;
                        colorPtr++;
                        depthPtr++;
                    }
                    w0_row += B12; w1_row += B20; w2_row += B01;
                }

            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Render time: " << std::chrono::duration<float, std::milli>(end - start).count() << "ms\n";
    }

    void run(Scene &scene, RenderTarget &image) {
        InitWindow(image.getWidth(), image.getHeight(), "rast");
        Texture2D texture = LoadTextureFromImage(GenImageColor(image.getWidth(), image.getHeight(), BLACK));
        std::vector<uint8_t> textureBytes(image.getWidth() * image.getHeight() * 4);

        while (!WindowShouldClose()) {
            auto start = std::chrono::high_resolution_clock::now();
            scene.update(image, GetFrameTime());
            render(image, scene.models, scene.camera);

            UpdateTexture(texture, image.colourBuffer.data());
            BeginDrawing();
            DrawTexture(texture, 0, 0, WHITE);
            EndDrawing();
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Frame time: " << std::chrono::duration<float, std::milli>(end - start).count() << "ms\n";
        }
        CloseWindow();
    }
}
