#ifndef RGB_COLOR_HPP
#define RGB_COLOR_HPP

#include <cstdint>

struct RGBColor {
  std::uint8_t red;
  std::uint8_t green;
  std::uint8_t blue;

  RGBColor() {}

  RGBColor(std::uint8_t red, std::uint8_t green, std::uint8_t blue)
      : red{red}, green{green}, blue{blue} {}
};

#endif