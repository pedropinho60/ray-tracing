#ifndef FILM_HPP
#define FILM_HPP

#include "common.hpp"
#include <cstdint>
#include <iostream>
#include <vector>

class Film {
private:
  const Point2 resolution;
  std::vector<RGBColor> buffer;

public:
  Film(std::uint16_t width, std::uint16_t height)
      : resolution{width, height},
        buffer{static_cast<size_t>(resolution.x * resolution.y)} {}

  void add_sample(const Point2 point, const RGBColor color) {
    buffer[point.y * resolution.x + point.x] = color;
  }

  void write_out() {
    for (auto color : buffer) {
      std::cout << (int)color.red << ' ' << (int)color.green << ' '
                << (int)color.blue << '\n';
    }
  }
};

#endif // FILM_HPP
