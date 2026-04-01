#ifndef POINT_2D_HPP
#define POINT_2D_HPP

#include <cstdint>

struct Point2D {
  std::uint16_t row;
  std::uint16_t col;

  Point2D(std::uint16_t row, std::uint16_t col) : row{row}, col{col} {}
};

#endif // POINT_2D_HPP
