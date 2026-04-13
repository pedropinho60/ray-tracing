#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "point_3d.hpp"
#include "ray.hpp"
#include "film.hpp"
#include "vector.hpp"
#include <memory>

class Camera {
protected:
    Point3D look_at, look_from;
    Vector up;
    
public:
    std::unique_ptr<Film> film;

    Camera() : look_at{}, look_from{}, up{} {}
    Camera(Point3D look_at, Point3D look_from, Vector up) : look_at{look_at}, look_from{look_from}, up{up} {}
    virtual ~Camera() = default;
    virtual Ray generate_ray(int row, int col) = 0;
};

#endif // CAMERA_HPP
