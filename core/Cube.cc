
#include <iostream>
#include "Cube.h"

using namespace Eigen;

Cube::Cube() {
	init();
	init_model_vertices();
	UpdateMetaData();
};

Cube::Cube(Vector3f& position, Vector3f& rotation, Vector3f& scale) {
	position_ = position;
	rotation_ = rotation;
	scale_ = scale;

	init_model_vertices();
	UpdateMetaData();
};

void Cube::init_model_vertices() {
	if (vertices_model_ != NULL) {
		delete(vertices_model_);
	}
	if (vertices_world_ != NULL) {
		delete(vertices_world_);
	}
	vertices_model_ = new Eigen::MatrixXf(8, 3);
	vertices_world_ = new Eigen::MatrixXf(8, 3);

	*vertices_model_ << -0.5, 0.5, -0.5,
		-0.5, -0.5, -0.5,
		-0.5, 0.5, 0.5,
		-0.5, -0.5, 0.5,
		0.5, 0.5, -0.5,
		0.5, -0.5, -0.5,
		0.5, -0.5, 0.5,
		0.5, 0.5, 0.5;
}

MatrixXf Cube::get_vertices() {
	Eigen::MatrixXf vertices_world_copy(vertices_world_->rows(), vertices_world_->cols());
	vertices_world_copy << *vertices_world_;
	return vertices_world_copy;
}

int Cube::get_num_vertices() { return 8; }

void Cube::init_faces() {
	faces_ = new MatrixXf(12, 3);
	false << 3, 2, 6,
		2, 6, 7,
		6, 7, 4,
		7, 4, 2,
		4, 2, 0,
		2, 0, 3,
		0, 3, 1,
		3, 1, 6,
		1, 6, 5,
		6, 5, 4,
		5, 4, 1,
		4, 1, 0;
}

MatrixXf Cube::get_faces() {
	Eigen::MatrixXf faces_copy(faces_->rows(), faces_->cols());
	faces_copy << *faces_;
	return faces_copy;
}