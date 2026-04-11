#ifndef PERSPECTIVE_CAMERA_HPP
#define PERSPECTIVE_CAMERA_HPP

#include "camera.hpp"
#include "param_set.hpp"
#include <memory>

class PerspectiveCamera : public Camera {
    int fovy;
    
public:
    PerspectiveCamera(Point3D look_at, Point3D look_from, Vector up, int fovy) : Camera(look_at, look_from, up), fovy{fovy} {}
    Ray generate_ray(int row, int col);
};

std::unique_ptr<PerspectiveCamera> create_perspective_camera(const ParamSet &ps, Point3D look_at,
                                  Point3D look_from, Vector up);

#endif // PERSPECTIVE_CAMERA_HPP
