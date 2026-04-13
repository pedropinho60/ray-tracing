#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "rgb_color.hpp"

class Material {
public:
    RGBColor color;

    Material(RGBColor color) : color{color} {}
};

#endif // MATERIAL_HPP
