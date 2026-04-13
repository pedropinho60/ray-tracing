#ifndef APP_HPP
#define APP_HPP

#include <memory>

#include "param_set.hpp"
#include "scene.hpp"

class App {
  static std::unique_ptr<Scene> scene;

  static Point3D look_from, look_at;
  static Vector up;

public:
  static void run(const char* filename);
  static void render();

  static void world_begin(const ParamSet &ps);
  static void world_end(const ParamSet &ps);
  static void create_background(const ParamSet &ps);
  static void create_film(const ParamSet &ps);
  static void create_object(const ParamSet &ps);
  static void lookat(const ParamSet &ps);
  static void create_camera(const ParamSet &ps);
};

#endif // APP_HPP
