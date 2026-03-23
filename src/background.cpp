#include <iostream>
#include <vector>

#include "../include/background.hpp"
#include "../include/common.hpp"

Background::Background(const std::vector<RGBColor> &colors) {
  corners[0] = colors[0];
  corners[1] = colors[1];
  corners[2] = colors[2];
  corners[3] = colors[3];
}

Background::Background(const Background* bg) {
  this->corners = bg->corners;
}

RGBColor Background::lerp(const RGBColor &A, const RGBColor &B, float t) const {
  return RGBColor((1 - t) * A.red + t * B.red, (1 - t) * A.green + t * B.green,
                  (1 - t) * A.blue + t * B.blue);
}

RGBColor Background::blerp(float normalized_row, float normalized_col) const {
  RGBColor top = lerp(corners[tl], corners[tr], normalized_col);
  RGBColor bot = lerp(corners[bl], corners[br], normalized_col);

  return lerp(top, bot, normalized_row);
}

Background* create_single_color_background(const ParamSet &ps) {
  auto color = ps.retrieve<RGBColor>("color");
  std::vector<RGBColor> colors = {4, color.value()};

  return new Background{colors};
}

Background* create_multicolor_background(const ParamSet &ps) {
  auto tl = ps.retrieve<RGBColor>("tl").value_or({});
  auto tr = ps.retrieve<RGBColor>("tr").value_or({});
  auto br = ps.retrieve<RGBColor>("br").value_or({});
  auto bl = ps.retrieve<RGBColor>("bl").value_or({});


  return new Background{{tl, tr, br, bl}};
}

