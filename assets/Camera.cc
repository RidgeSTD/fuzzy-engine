#include "Camera.h"
#include "math.h"

using namespace Eigen;

Camera::Camera() {
  position_ = Vector3f(0, 0, 0);
  front_ = Vector3f(0, 0, 1);
  up_ = Vector3f(0, 1, 0);
  right_ = Vector3f(1, 0, 0);
  fov_ = M_PI / 2;
  near_ = 0.1;
  far_ = 10;
};

bool Camera::LookAt(Vector3f target, Vector3f new_up) {
  return true;
}