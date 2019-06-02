#include "Camera.h"
#include "math.h"

using namespace Eigen;

Camera::Camera() {
  position = Vector3f(0, 0, 0);
  front = Vector3f(0, 0, 1);
  up = Vector3f(0, 1, 0);
  right = Vector3f(1, 0, 0);
  fov = M_PI / 2;
  near = 0.1;
  far = 10;
};