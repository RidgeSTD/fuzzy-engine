#include "Cube.h"
#include "core.h"

Cube::Cube()
{
    position = Vector3();
    rotation = Vector3();
    size = Vector3();
};

Cube::Cube(Vector3 _position, Vector3 _rotation, Vector3 _size)
{
    position = _position;
    rotation = _rotation;
    size = _size;
};