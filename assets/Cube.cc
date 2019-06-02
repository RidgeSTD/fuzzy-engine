#include "Cube.h"

using namespace Eigen;

Cube::Cube() {
  position = Vector3f();
  rotation = Vector3f();
  size = Vector3f();
};

Cube::Cube(Vector3f _position, Vector3f _rotation, Vector3f _size) {
  position = _position;
  rotation = _rotation;
  size = _size;
};