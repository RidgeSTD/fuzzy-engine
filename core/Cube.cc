#include <iostream>
#include "Cube.h"

using namespace Eigen;

Cube::Cube() {
	position_ = Eigen::Vector3f(0, 0, 0);
	rotation_ = Eigen::Vector3f(0, 0, 0);
	scale_ = Eigen::Vector3f(1, 1, 1);
	
	init_model_vertices();
	UpdateMetaData();
};

Cube::Cube(Vector3f position, Vector3f rotation, Vector3f scale) {
	position_ = position;
	rotation_ = rotation;
	scale_ = scale;

	init_model_vertices();
	UpdateMetaData();
};

void Cube::init_model_vertices() {
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