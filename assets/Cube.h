#ifndef CUBE_H
#define CUBE_H
#include "core.h"


class Cube {
public:
  Eigen::Vector3f position, rotation, size;
  Cube();
  Cube(Eigen::Vector3f _position, Eigen::Vector3f _rotation, Eigen::Vector3f _size);
};
#endif // CUBE_H