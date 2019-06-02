#ifndef CUBE_H
#define CUBE_H
#include "core.h"

class Cube {
public:
  Vector3 position, rotation, size;
  Cube();
  Cube(Vector3 _position, Vector3 _rotation, Vector3 _size);
};
#endif // CUBE_H