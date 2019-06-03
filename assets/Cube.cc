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
	Matrix3f rotation_matrix = rotation_quaternion_.matrix();
  for (size_t i = 0; i < 8; i++) {
    vertices_[i] = position_ + vertices_offsets_[i].cwiseProduct(size_);
	vertices_[i] = rotation_matrix * vertices_[i];
  }

  return vertices_;
}

int Cube::get_num_vertices() { return 8; }

bool Cube::set_rotation(Vector3f new_euler_rotation) {
	rotation_ = new_euler_rotation;
	AngleAxisf r(rotation_.z(), Vector3f::UnitZ());
	AngleAxisf y(rotation_.y(), Vector3f::UnitY());
	AngleAxisf p(rotation_.x(), Vector3f::UnitX());
	rotation_quaternion_ = r * y * p;
	return true;
}