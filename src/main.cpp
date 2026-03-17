#include <cstdint>
#include <iostream>

#include "background.hpp"
#include "common.hpp"

int main() {
  const std::uint16_t width{400};
  const std::uint16_t height{200};
  const std::uint8_t max_channel_value{255};

  Background bg{{RGBColor(0, 255, 51), RGBColor(255, 255, 51),
                 RGBColor(255, 0, 51), RGBColor(0, 0, 51)}};

  std::cout << "P3\n";
  std::cout << width << ' ' << height << '\n';
  std::cout << (int)max_channel_value << '\n';

  for (std::uint16_t row{0}; row < height; ++row) {
    float v = static_cast<float>(row) / (height - 1);
    for (std::uint16_t col{0}; col < width; ++col) {
      float u = static_cast<float>(col) / (width - 1);
      RGBColor color = bg.sampleUV(u, v);
      std::cout << (int)color.red << ' ' << (int)color.green << ' '
                << (int)color.blue << '\n';
    }
  }
}
