#ifndef FILM_HPP
#define FILM_HPP

#include "common.hpp"
#include <vector>

class Film {
private:
  const Point2 resolution;
  std::vector<RGBColor> buffer;

public:
  Film(Point2 resolution) : resolution(resolution) {
      buffer.reserve(resolution.x * resolution.y);
  }

  void add_sample(const Point2 point, const RGBColor color) {
      buffer[point.y * resolution.x + point.x] = color;
  }
};

#endif // FILM_HPP
