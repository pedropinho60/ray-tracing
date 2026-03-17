#ifndef COMMON_HPP
#define COMMON_HPP

#include <cstdint>

struct RGBColor {
  std::uint8_t red;
  std::uint8_t green;
  std::uint8_t blue;
  RGBColor(std::uint8_t red, std::uint8_t green, std::uint8_t blue)
      : red{red}, green{green}, blue{blue} {}
};

struct Point2 {
  std::uint16_t x;
  std::uint16_t y;
  Point2(std::uint16_t x, std::uint16_t y) : x{x}, y{y} {}
};

#endif // COMMON_HPP
