#include <cassert>
#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "../include/app.hpp"
#include "../include/background.hpp"
#include "../include/film.hpp"
#include "../include/parser.hpp"
#include "../include/orthographic_camera.hpp"
#include "../include/perspective_camera.hpp"
#include "../include/sphere.hpp"

std::unique_ptr<Scene> App::scene;

Point3D App::look_from, App::look_at;
Vector App::up;

void App::run(const char* filename) {
  scene = std::make_unique<Scene>();
  Parser::parse(filename);
}

void App::render() {
  for (std::uint16_t row{0}; row < scene->camera->film->height; ++row) {
    float normalized_row = static_cast<float>(row) / (scene->camera->film->height - 1);

    for (std::uint16_t col{0}; col < scene->camera->film->width; ++col) {
      Ray ray = scene->camera->generate_ray(row, col);

      // std::cout << "pixel(" << row << "," << col << "), Ray: " << ray << "\n";

      RGBColor color;

      float normalized_col = static_cast<float>(col) / (scene->camera->film->width - 1);
      color = scene->background->blerp(normalized_row, normalized_col);

      for (auto p : scene->primitives) {
        if (p->intersect_p(ray)) {
          color = RGBColor{255, 0, 0};
        }
      }

      scene->camera->film->add_sample({row, col}, color);
    }
  }

  scene->camera->film->write_image();
}

void App::create_background(const ParamSet &ps) {
  auto color = ps.retrieve<RGBColor>("color");

  Background *bg{nullptr};

  if (!color) {
    bg = create_multicolor_background(ps);
  } else {
    bg = create_single_color_background(ps);
  }

  scene->background = std::make_unique<Background>(bg);
}

void App::create_film(const ParamSet &ps) {
  assert(scene->camera && "camera is null in create_film");

  auto w_res = ps.retrieve<std::uint16_t>("w_res").value_or({});
  auto h_res = ps.retrieve<std::uint16_t>("h_res").value_or({});

  auto filename = ps.retrieve<std::string>("filename").value_or({});
  auto filetype = ps.retrieve<std::string>("img_type").value_or({});

  scene->camera->film = std::make_unique<Film>(w_res, h_res, filename, filetype);
}

void App::lookat(const ParamSet &ps) {
  look_from = ps.retrieve<Point3D>("look_from").value_or({});
  look_at = ps.retrieve<Point3D>("look_at").value_or({});
  up = ps.retrieve<Vector>("up").value_or({});
}

void App::create_camera(const ParamSet &ps) {
  auto type = ps.retrieve<std::string>("type").value();

  if (type == "orthographic") {
    scene->camera = create_orthographic_camera(ps, look_at, look_from, up);
  } else {
    scene->camera = create_perspective_camera(ps, look_at, look_from, up);
  }
}

void App::create_object(const ParamSet &ps) {
  auto type = ps.retrieve<std::string>("type").value();

  if (type == "sphere") {
    scene->primitives.push_back(std::make_shared<Sphere>(create_sphere(ps)));
  } else {
    throw std::runtime_error("unknown object type: `" + type + "`");
  }
}

void App::world_begin(const ParamSet &ps) {}

void App::world_end(const ParamSet &ps) {
}
