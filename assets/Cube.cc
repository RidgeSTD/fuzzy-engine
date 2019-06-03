#include "Cube.h"

using namespace Eigen;

Cube::Cube() {
  position_ = Vector3f(0, 0, 0);
  rotation_ = Vector3f(0, 0, 0);
  size_ = Vector3f(1, 1, 1);
};

Cube::Cube(Vector3f position, Vector3f rotation, Vector3f size) {
  position_ = position;
  rotation_ = rotation;
  size_ = size;
};

Vector3f* Cube::get_vertices() {
  for (size_t i = 0; i < 8; i++) {
    vertices_[i] = position_ + vertices_offsets_[i].cwiseProduct(size_);
  }

  return vertices_;
}

int Cube::get_num_vertices() { return 8; }