#include <cstdint>
#include <memory>

#include "../include/app.hpp"
#include "../include/background.hpp"
#include "../include/film.hpp"
#include "../include/parser.hpp"

std::unique_ptr<Film> App::film;
std::unique_ptr<Background> App::bg;

void App::run(const char* filename) {
  Parser::parse(filename);
}

void App::render() {
  for (std::uint16_t row{0}; row < film->height; ++row) {
    float normalized_row = static_cast<float>(row) / (film->height - 1);

    for (std::uint16_t col{0}; col < film->width; ++col) {
      float normalized_col = static_cast<float>(col) / (film->width - 1);
      RGBColor color = bg->blerp(normalized_row, normalized_col);

      film->add_sample({row, col}, color);
    }
  }

  film->write_image();
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
  auto x_res = ps.retrieve<std::uint16_t>("x_res").value_or({});
  auto y_res = ps.retrieve<std::uint16_t>("y_res").value_or({});

  auto filename = ps.retrieve<std::string>("filename").value_or({});
  auto filetype = ps.retrieve<std::string>("img_type").value_or({});

  App::film = std::make_unique<Film>(x_res, y_res, filename, filetype);
}

void App::world_begin(const ParamSet &ps) {}
void App::world_end(const ParamSet &ps) {}
