#ifndef FILM_HPP
#define FILM_HPP

#include "common.hpp"
#include <cstdint>
#include <iostream>
#include <vector>

class Film {
private:
  const std::uint16_t width;
  const std::uint16_t height;
  std::vector<RGBColor> buffer;

public:
  Film(std::uint16_t width, std::uint16_t height)
      : width{width},  height{height},
        buffer{static_cast<size_t>(width * height)} {}

  void add_sample(const std::uint16_t row, const std::uint16_t col, const RGBColor color) {
    buffer[row * width + col] = color;
  }

  void write_ppm() {
    for (auto color : buffer) {
      std::cout << (int)color.red << ' ' << (int)color.green << ' '
                << (int)color.blue << '\n';
    }
  }
};

#endif // FILM_HPP
