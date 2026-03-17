#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <array>
#include <vector>

#include "common.hpp"

class Background {
private:
  /// Each corner has a color associated with.
  std::array<RGBColor, 4> corners{RGBColor{0, 0, 0}, RGBColor{0, 0, 0},
                                  RGBColor{0, 0, 0}, RGBColor{0, 0, 0}};
  /// Corner indices.
  enum Corners_e {
    tl = 0, //!< Top left corner.
    tr,     //!< Top right corner.
    br,     //!< Bottom right corner.
    bl      //!< Bottom left corner.
  };

  /// Return the linearly interpolated color in [A;B], based on the parameter
  /// \f$0\leq t \leq 1.\f$
  RGBColor lerp(const RGBColor &A, const RGBColor &B, float t) const {
    return RGBColor((1 - t) * A.red + t * B.red,
                    (1 - t) * A.green + t * B.green,
                    (1 - t) * A.blue + t * B.blue);
  }

public:
  /// Ctro receives a list of four colors, for each corner.
  Background(const std::vector<RGBColor> &colors) {
    corners[0] = colors[0];
    corners[1] = colors[1];
    corners[2] = colors[2];
    corners[3] = colors[3];
  }
  /// Dtro
  ~Background() {};
  /// Sample and returns a color, based on the raster coordinate.
  RGBColor sampleUV(float u, float v) const {
    RGBColor top = lerp(corners[tl], corners[tr], u);
    RGBColor bot = lerp(corners[bl], corners[br], u);

    return lerp(top, bot, v);
  }
};

#endif // BACKGROUND_HPP
