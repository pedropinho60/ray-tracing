#include "app.hpp"

void App::render() {
  for (std::uint16_t row{0}; row < height; ++row) {
    float normalized_row = static_cast<float>(row) / (height - 1);

    for (std::uint16_t col{0}; col < width; ++col) {
      float normalized_col = static_cast<float>(col) / (width - 1);
      RGBColor color = bg.sampleUV(normalized_row, normalized_col);

      film.add_sample({row, col}, color);
    }
  }

  film.write_ppm();
}
