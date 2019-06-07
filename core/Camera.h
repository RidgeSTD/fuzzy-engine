#ifndef CAMERA_H
#define CAMERA_H

#include "common_include.h"

class Camera
{

public:
	Eigen::Vector3f position_, front_, up_, left_;
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	float fov_, far_, near_;
	Camera();

	bool LookAt(Eigen::Vector3f target, Eigen::Vector3f new_up);
	bool rotate(Eigen::Matrix3f rotationMatrix);
	Eigen::Matrix4f get_V();
	Eigen::Matrix4f get_P();
	Eigen::Matrix4f get_VP();

private:
	Eigen::Matrix4f V_;
	Eigen::Matrix4f P_;
	Eigen::Matrix4f VP_;
	void update_V();
};

#endif // CAMERA_H