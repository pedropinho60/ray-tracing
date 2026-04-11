#ifndef FILM_HPP
#define FILM_HPP

#include <cstdint>
#include <string>
#include <vector>

#include "rgb_color.hpp"
#include "point_2d.hpp"

class Film {
public:
  const std::uint16_t width;
  const std::uint16_t height;

  const std::string filename;

  enum image_type {
    PPM,
    PNG,
  };

  image_type filetype;

private:
  const std::uint8_t max_channel_value{255};
  std::vector<RGBColor> buffer;

public:
  Film(std::uint16_t width, std::uint16_t height, std::string filename, std::string filetype);

  void add_sample(const Point2D point, const RGBColor color);
  void write_image();
  void write_ppm();
  void write_png();
};

#endif // FILM_HPP
