#include <cassert>
#include <cstdint>
#include <iostream>
#include <memory>

#include "../include/app.hpp"
#include "../include/background.hpp"
#include "../include/film.hpp"
#include "../include/parser.hpp"
#include "../include/orthographic_camera.hpp"
#include "../include/perspective_camera.hpp"

std::unique_ptr<Camera> App::camera;
std::unique_ptr<Background> App::bg;

Point3D App::look_from, App::look_at;
Vector App::up;

void App::run(const char* filename) {
  Parser::parse(filename);
}

void App::render() {
  for (std::uint16_t row{0}; row < camera->film->height; ++row) {
    float normalized_row = static_cast<float>(row) / (camera->film->height - 1);

    for (std::uint16_t col{0}; col < camera->film->width; ++col) {
      Ray ray = camera->generate_ray(row, col);

      std::cout << "pixel(" << row << "," << col << "), Ray: " << ray << "\n";

      float normalized_col = static_cast<float>(col) / (camera->film->width - 1);
      RGBColor color = bg->blerp(normalized_row, normalized_col);

      camera->film->add_sample({row, col}, color);
    }
  }

  camera->film->write_image();
}

void App::create_background(const ParamSet &ps) {
  auto color = ps.retrieve<RGBColor>("color");

  Background *bg{nullptr};

  if (!color) {
    bg = create_multicolor_background(ps);
  } else {
    bg = create_single_color_background(ps);
  }

  App::bg = std::make_unique<Background>(bg);
}

void App::create_film(const ParamSet &ps) {
  assert(camera && "camera is null in create_film");

  auto w_res = ps.retrieve<std::uint16_t>("w_res").value_or({});
  auto h_res = ps.retrieve<std::uint16_t>("h_res").value_or({});

  auto filename = ps.retrieve<std::string>("filename").value_or({});
  auto filetype = ps.retrieve<std::string>("img_type").value_or({});

  camera->film = std::make_unique<Film>(w_res, h_res, filename, filetype);
}

void App::lookat(const ParamSet &ps) {
  look_from = ps.retrieve<Point3D>("look_from").value_or({});
  look_at = ps.retrieve<Point3D>("look_at").value_or({});
  up = ps.retrieve<Vector>("up").value_or({});
}

void App::create_camera(const ParamSet &ps) {
  auto type = ps.retrieve<std::string>("type").value();

  if (type == "orthographic") {
    camera = create_orthographic_camera(ps, look_at, look_from, up);
  } else {
    camera = create_perspective_camera(ps, look_at, look_from, up);
  }
}

void App::world_begin(const ParamSet &ps) {}
void App::world_end(const ParamSet &ps) {}
