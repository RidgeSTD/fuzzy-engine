#include "Cube.h"

using namespace Eigen;

Cube::Cube() {
  position_ = Vector3f();
  rotation_ = Vector3f();
  size_ = Vector3f();
};

Cube::Cube(Vector3f position, Vector3f rotation, Vector3f size) {
  position_ = position;
  rotation_ = rotation;
  size_ = size;
};