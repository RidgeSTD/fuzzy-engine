#ifndef CAMERA_H
#define CAMERA_H

#include "core.h"

class Camera {
public:
  Eigen::Vector3f position_, front_, up_, right_;
  float fov_, far_, near_;
  Camera();

  bool LookAt(Eigen::Vector3f target, Eigen::Vector3f new_up);
};

#endif // CAMERA_H