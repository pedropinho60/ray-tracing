#include "../include/ortographic_camera.hpp"
#include "ortographic_camera.hpp"

Ray OrtographicCamera::generate_ray(int row, int col) {
    double x = row / film.height;
    double y = col / film.width;

    double z = left + x * (right - left);
    double w = bottom + y * (top - bottom);
}