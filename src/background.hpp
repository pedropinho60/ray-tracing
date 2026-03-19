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
  RGBColor lerp(const RGBColor &A, const RGBColor &B, float t) const;

public:
  /// Ctro receives a list of four colors, for each corner.
  Background(const std::vector<RGBColor> &colors);
  /// Dtro
  ~Background() {};
  /// Sample and returns a color, based on the raster coordinate.
  RGBColor sampleUV(float normalized_row, float normalized_col) const;
};

#endif // BACKGROUND_HPP
