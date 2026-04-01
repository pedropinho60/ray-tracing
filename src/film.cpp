#include <fstream>
#include <iomanip>
#include <iostream>

#include "../include/film.hpp"
#include "../include/point.hpp"
#include "../lib_lodepng/lodepng.h"

Film::Film(std::uint16_t width, std::uint16_t height, std::string filename,
           std::string filetype)
    : width{width}, height{height}, filename{filename},
      buffer{static_cast<size_t>(width * height)} {
  if (filetype == "png") {
    this->filetype = PNG;
  } else if (filetype == "ppm") {
    this->filetype = PPM;
  } else {
    std::string filetype_guess;

    size_t pos = filename.find_last_of('.');

    if (pos == std::string::npos) {
      filetype_guess = "";
    } else {
      filetype_guess = filename.substr(pos + 1);
    }

    if (filetype_guess == "png") {
      this->filetype = PNG;
    } else {
      this->filetype = PPM;
    }
  }
}

void Film::add_sample(const Point2D point, const RGBColor color) {
  buffer[point.row * width + point.col] = color;
}

void Film::write_image() {
  switch (filetype) {
    case PPM:
      write_ppm();
      break;
    case PNG:
      write_png();
      break;
  }
}

void Film::write_ppm() {
  std::ofstream file{filename};

  if (!file.is_open()) {
    std::ostringstream msg;
    msg << "Error opening file " << std::quoted(filename);
    throw std::runtime_error(msg.str());
  }

  file << "P3\n";
  file << width << ' ' << height << '\n';
  file << (int)max_channel_value << '\n';

  for (auto color : buffer) {
    file << (int)color.red << ' ' << (int)color.green << ' ' << (int)color.blue
         << '\n';
  }

  file.close();
}

void Film::write_png() {
  static_assert(sizeof(RGBColor) == 3, "RGBColor must be tightly packed");

  unsigned error = lodepng::encode(
    filename,
    reinterpret_cast<const unsigned char*>(buffer.data()),
    width,
    height,
    LCT_RGB,
    8
  );

  if (error) {
    std::ostringstream msg;
    msg << "PNG encode error " << error
        << ": " << lodepng_error_text(error);
    throw std::runtime_error(msg.str());
  }
}
