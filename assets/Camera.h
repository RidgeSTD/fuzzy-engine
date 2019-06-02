#ifndef CAMERA_H
#define CAMERA_H

#include "core.h"

class Camera {
public:
  Eigen::Vector3f position, front, up, right;
  float fov, far, near;
  Camera();
};

#endif // CAMERA_H