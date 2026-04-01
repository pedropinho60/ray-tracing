#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "ray.hpp"
#include "film.hpp"

class Camera {
    Film film;
    
    Ray generate_ray(int row, int col);
};

#endif // CAMERA_HPP