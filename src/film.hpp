#ifndef FILM_HPP
#define FILM_HPP

#include "common.hpp"
#include <cstdint>
#include <vector>

class Film {
public:
  const std::uint16_t width;
  const std::uint16_t height;
private:
  const std::uint8_t max_channel_value{255};
  std::vector<RGBColor> buffer;

public:
  Film(std::uint16_t width, std::uint16_t height);

  void add_sample(const Point point, const RGBColor color);
  void write_ppm();
};

#endif // FILM_HPP
