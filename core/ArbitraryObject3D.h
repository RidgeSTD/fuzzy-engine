#ifndef ARBITRARY_OBJECT_H
#define ARBITRARY_OBJECT_H

#include "common_include.h"
#include "Object3D.h"

class ArbitraryObject3D : public Object3D {
public:
	ArbitraryObject3D();
	ArbitraryObject3D(const std::string obj_file_name);
	int get_num_vertices();
	Eigen::MatrixXf get_vertices();
	Eigen::MatrixXf get_faces();
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

#endif // !ARBITRARY_OBJECT_H
