#ifndef ORTOGRAPHIC_CAMERA_HPP
#define ORTOGRAPHIC_CAMERA_HPP

#include "camera.hpp"

class OrtographicCamera : public Camera {
    Film film;
    double left, right, bottom, top;

    Ray generate_ray(int row, int col);
};

#endif // ORTOGRAPHIC_CAMERA_HPP