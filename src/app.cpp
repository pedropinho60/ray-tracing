#include "app.hpp"
#include "background.hpp"
#include "film.hpp"
#include <memory>

std::unique_ptr<Film> App::film;
std::unique_ptr<Background> App::bg;

void App::render() {
  for (std::uint16_t row{0}; row < film->height; ++row) {
    float normalized_row = static_cast<float>(row) / (film->height - 1);

    for (std::uint16_t col{0}; col < film->width; ++col) {
      float normalized_col = static_cast<float>(col) / (film->width - 1);
      RGBColor color = bg->blerp(normalized_row, normalized_col);

      film->add_sample({row, col}, color);
    }
  }

  film->write_ppm();
}
