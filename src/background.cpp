#include "../include/background.hpp"

Background::Background(const std::vector<RGBColor> &colors) {
  corners[0] = colors[0];
  corners[1] = colors[1];
  corners[2] = colors[2];
  corners[3] = colors[3];
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
