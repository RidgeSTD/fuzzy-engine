#ifndef ARBITRARY_OBJECT_H
#define ARBITRARY_OBJECT_H

#include "common_include.h"
#include "Object3D.h"

class ArbitraryObject3D : public Object3D {
public:
	ArbitraryObject3D();
	int get_num_vertices();
	Eigen::MatrixXf get_vertices();
protected:
	Eigen::MatrixXf vertices_;
	Eigen::MatrixXf faces_;
};

#endif // !ARBITRARY_OBJECT_H
