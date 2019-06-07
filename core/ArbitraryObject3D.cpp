#include "ArbitraryObject3D.h"

using namespace Eigen;

ArbitraryObject3D::ArbitraryObject3D(){

}

int ArbitraryObject3D::get_num_vertices(){
	return vertices_.rows();
}

MatrixXf ArbitraryObject3D ::get_vertices() {
	Eigen::MatrixXf vertices_world_copy(vertices_world_->rows(), vertices_world_->cols());
	vertices_world_copy << *vertices_world_;
	return vertices_world_copy;
}