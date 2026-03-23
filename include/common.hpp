#ifndef COMMON_HPP
#define COMMON_HPP

#include <cstdint>
#include <stdexcept>

struct RGBColor {
  std::uint8_t red;
  std::uint8_t green;
  std::uint8_t blue;

  RGBColor() {}
  RGBColor(std::uint8_t red, std::uint8_t green, std::uint8_t blue)
      : red{red}, green{green}, blue{blue} {}

  std::uint8_t& operator[](int index) {
    switch(index) {
      case 0:
        return red;
      case 1:
        return green;
      case 2:
        return blue;
      default:
        throw std::out_of_range("Index out of bounds");
    }
  }
};

struct Point {
  std::uint16_t row;
  std::uint16_t col;

  Point(std::uint16_t row, std::uint16_t col) : row{row}, col{col} {}
};

#endif // COMMON_HPP
