#ifndef FILM_HPP
#define FILM_HPP

#include "common.hpp"
#include <cstdint>
#include <vector>

class Film {
private:
  const std::uint16_t width;
  const std::uint16_t height;
  const std::uint8_t max_channel_value;
  std::vector<RGBColor> buffer;

public:
  Film(std::uint16_t width, std::uint16_t height,
       std::uint8_t max_channel_value);

  void add_sample(const Point point,
                  const RGBColor color);

  void write_ppm();
};

#endif // FILM_HPP
