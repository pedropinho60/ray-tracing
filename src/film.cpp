#include <iostream>

#include "film.hpp"

Film::Film(std::uint16_t width, std::uint16_t height,
           std::uint8_t max_channel_value)
    : width{width}, height{height}, max_channel_value{max_channel_value},
      buffer{static_cast<size_t>(width * height)} {}

void Film::add_sample(const Point point,
                      const RGBColor color) {
  buffer[point.row * width + point.col] = color;
}

void Film::write_ppm() {
  std::cout << "P3\n";
  std::cout << width << ' ' << height << '\n';
  std::cout << (int)max_channel_value << '\n';

  for (auto color : buffer) {
    std::cout << (int)color.red << ' ' << (int)color.green << ' '
              << (int)color.blue << '\n';
  }
}
