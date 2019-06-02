#ifndef CUBE_H
#define CUBE_H
#include "core.h"


class Cube {
public:
  Eigen::Vector3f position_, rotation_, size_;
  Cube();
  Cube(Eigen::Vector3f position, Eigen::Vector3f rotation, Eigen::Vector3f size);
};
#endif // CUBE_H