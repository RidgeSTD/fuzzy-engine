#ifndef CUBE_H
#define CUBE_H
#include "Object3D.h"
#include "core.h"

class Cube : public Object3D {
public:
	Eigen::Vector3f position_, rotation_, size_;
	Eigen::Quaternion<float> rotation_quaternion_;
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	Cube();
	Cube(Eigen::Vector3f position, Eigen::Vector3f rotation,
		Eigen::Vector3f size);
	Eigen::Vector3f* get_vertices();
	int get_num_vertices();
	bool set_rotation(Eigen::Vector3f new_euler_rotation);

private:
	Eigen::Vector3f vertices_[8];
	Eigen::Vector3f vertices_offsets_[8] = {
	Eigen::Vector3f(-0.5, 0.5, -0.5),  Eigen::Vector3f(-0.5, -0.5, -0.5),
	Eigen::Vector3f(-0.5, 0.5, 0.5),    Eigen::Vector3f(-0.5, -0.5, 0.5),
	Eigen::Vector3f(0.5, 0.5, -0.5), Eigen::Vector3f(0.5, -0.5, -0.5),
	Eigen::Vector3f(0.5, -0.5, 0.5),   Eigen::Vector3f(0.5, 0.5, 0.5)};
};
#endif // CUBE_H