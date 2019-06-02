#include "Camera.h"
#include "math.h"

using namespace Eigen;

Camera::Camera() {
  // position_, front_, right_ and up_ are in world coordinate
  position_ = Vector3f(0, 0, 0);
  right_ = Vector3f(1, 0, 0);
  up_ = Vector3f(0, 1, 0);
  front_ = Vector3f(0, 0, 1);
  fov_ = M_PI / 2;
  near_ = 0.1;
  far_ = 10;

  V_.setIdentity();
  // TODO: projection to be done
  // P_.setIdentity();
  // VP_.setIdentity();
};

bool Camera::LookAt(Vector3f target, Vector3f new_up) { return true; }

Matrix4f Camera::get_V() {

  V_.block<3, 1>(0, 0) << right_;
  V_.block<3, 1>(0, 1) << up_;
  V_.block<3, 1>(0, 2) << front_;
  V_.block<3, 1>(3, 0) << position_;
  V_ << V_.inverse();
  return V_;
};
Matrix4f Camera::get_P() { return P_; };
Matrix4f Camera::get_VP() { return VP_; };