#ifndef ORTHOGRAPHIC_CAMERA_HPP
#define ORTHOGRAPHIC_CAMERA_HPP

#include "camera.hpp"
#include "param_set.hpp"
#include "window_size.hpp"

class OrthographicCamera : public Camera {
    double left, right, bottom, top;

  public:
    OrthographicCamera(WindowSize dimensions, Point3D look_at, Point3D look_from,
                      Vector up);
    Ray generate_ray(int row, int col);
};

std::unique_ptr<OrthographicCamera> create_orthographic_camera(const ParamSet &ps, Point3D look_at, Point3D look_from, Vector up);

#endif // ORTHOGRAPHIC_CAMERA_HPP
