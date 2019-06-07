#ifndef CUBE_H
#define CUBE_H
#include "Object3D.h"
#include "common_include.h"

class Cube : public Object3D
{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	Cube();
	Cube(Eigen::Vector3f& position, Eigen::Vector3f& rotation,
		 Eigen::Vector3f& scale);
	Eigen::MatrixXf get_vertices();
	Eigen::MatrixXf get_faces();
	int get_num_vertices();
	

private:
	Eigen::Vector3f vertices_offsets_[8] = {
		Eigen::Vector3f(-0.5, 0.5, -0.5), Eigen::Vector3f(-0.5, -0.5, -0.5),
		Eigen::Vector3f(-0.5, 0.5, 0.5), Eigen::Vector3f(-0.5, -0.5, 0.5),
		Eigen::Vector3f(0.5, 0.5, -0.5), Eigen::Vector3f(0.5, -0.5, -0.5),
		Eigen::Vector3f(0.5, -0.5, 0.5), Eigen::Vector3f(0.5, 0.5, 0.5)};
	void init_model_vertices();
	void init_faces();
};
#endif // CUBE_H