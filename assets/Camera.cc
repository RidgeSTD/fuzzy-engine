#include "Camera.h"
#include "math.h"

Camera::Camera() {
  position = Vector3();
  front = Vector3(0, 0, 1);
  up = Vector3(0, 1, 0);
  right = Vector3(1, 0, 0);
  fov = M_PI / 2;
  near = 0.1;
  far = 10;
};