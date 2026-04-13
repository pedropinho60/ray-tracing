#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>

#include "background.hpp"
#include "camera.hpp"
#include "primitive.hpp"

class Scene {
public:
    std::unique_ptr<Camera> camera;
    std::unique_ptr<Background> background;
    std::vector<std::shared_ptr<Primitive>> primitives;

    Scene() {};
    Scene(std::unique_ptr<Camera> camera, std::unique_ptr<Background> background, std::vector<std::shared_ptr<Primitive>> primitives)
        : camera{std::move(camera)}, background{std::move(background)}, primitives{primitives} {}
};

#endif // SCENE_HPP
