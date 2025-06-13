cmake_minimum_required(VERSION 3.30)
project(softwareRasterizer)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/dependencies/raylib/include)
link_directories(${CMAKE_SOURCE_DIR}/dependencies/raylib/lib)

add_executable(softwareRasterizer src/main.cpp
        include/math.hpp
        src/math.cpp
        include/util.hpp
        src/util.cpp
        include/render.hpp
        src/render.cpp
        include/image.hpp
        src/image.cpp
        include/objParser.hpp
        src/objParser.cpp
        src/rendertarget.cpp
        include/rendertarget.hpp
        src/model.cpp
        include/model.hpp
        src/transform.cpp
        include/transform.hpp
        src/scene.cpp
        include/scene.hpp
        src/camera.cpp
        include/camera.hpp)

target_link_libraries(${PROJECT_NAME}
        raylib
        opengl32
        gdi32
        winmm
)