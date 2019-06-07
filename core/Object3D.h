#ifndef OBJECT_3D
#define OBJECT_3D

#include "common_include.h"

class Object3D
{
public:
	Eigen::Matrix4f ModelToWorldMatrix_;
	virtual Eigen::MatrixXf get_vertices() = 0;
    virtual int get_num_vertices() = 0;
	virtual Eigen::MatrixXf get_faces() = 0;
	void init() {
		position_ = Eigen::Vector3f(0, 0, 0);
		rotation_ = Eigen::Vector3f(0, 0, 0);
		rotation_quaternion_ = Eigen::Quaternion<float>(1, 0, 0, 0);
		scale_ = Eigen::Vector3f(1, 1, 1);
		vertices_model_ = new Eigen::MatrixXf();
		vertices_world_ = new Eigen::MatrixXf();
		faces_ = new Eigen::MatrixXf();
		UpdateMetaData();
	}

	void set_position(Eigen::Vector3f& position) {
		position_ = position;
		UpdateMetaData();
	}
	void set_rotation(Eigen::Vector3f& new_euler_rotation) {
		rotation_ = new_euler_rotation;
		UpdateMetaData();
	};
	void set_scale(Eigen::Vector3f& scale) {
		scale_ = scale;
		UpdateMetaData();
	};

protected:
	Eigen::Vector3f position_, rotation_, scale_;
	Eigen::Quaternion<float> rotation_quaternion_;
	Eigen::MatrixXf* vertices_model_;
	Eigen::MatrixXf* vertices_world_;
	Eigen::MatrixXf* faces_;

	// update vertices_world_ and rotation_quaternion acordingly
	void UpdateMetaData() {
		Eigen::AngleAxisf r(rotation_.z(), Eigen::Vector3f::UnitZ());
		Eigen::AngleAxisf y(rotation_.y(), Eigen::Vector3f::UnitY());
		Eigen::AngleAxisf p(rotation_.x(), Eigen::Vector3f::UnitX());
		rotation_quaternion_ = r * y * p;
		ModelToWorldMatrix_.block<3, 3>(0, 0) = rotation_quaternion_.matrix();
		ModelToWorldMatrix_.col(3).head(3) = position_;
		ModelToWorldMatrix_.row(3).head(3).setZero();
		ModelToWorldMatrix_(3, 3) = 1;
		Eigen::Vector3f v;

		vertices_world_->resize(vertices_model_->rows(), vertices_model_->cols());
		for (size_t i = 0; i < vertices_world_->rows(); i++)
		{
			v = vertices_model_->row(i);
			vertices_world_->row(i) = (ModelToWorldMatrix_ * Eigen::Vector4f(v.x() * scale_.x(), v.y() * scale_.y(), v.z() * scale_.z(), 1)).head(3);
		}
	};
};

#endif