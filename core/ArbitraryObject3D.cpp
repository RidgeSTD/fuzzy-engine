#include "ArbitraryObject3D.h"
#include "igl/readOBJ.h"
#include <direct.h>
#include <stdio.h>

using namespace Eigen;

ArbitraryObject3D::ArbitraryObject3D() {}
ArbitraryObject3D::ArbitraryObject3D(std::string obj_file_name) {
	init();
	bool load_success = igl::readOBJ(obj_file_name, *vertices_model_, *faces_);
	if (!load_success) {
		printf("Fail to load OBJ file!\n");
		exit(-1);
	}
	UpdateMetaData();
}

int ArbitraryObject3D::get_num_vertices() {
	return vertices_model_->rows();
}

MatrixXf ArbitraryObject3D::get_vertices() {
	Eigen::MatrixXf vertices_world_copy(vertices_world_->rows(), vertices_world_->cols());
	vertices_world_copy << *vertices_world_;
	return vertices_world_copy;
}

MatrixXf ArbitraryObject3D::get_faces() {
	Eigen::MatrixXf faces_copy(faces_->rows(), faces_->cols());
	faces_copy << *faces_;
	return faces_copy;
}