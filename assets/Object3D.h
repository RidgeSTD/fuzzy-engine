#ifndef OBJECT_3D
#define OBJECT_3D

#include "core.h"

class Object3D{
    public:
        virtual Eigen::Vector3f* get_vertices() = 0;
        virtual int get_num_vertices() = 0;
};

#endif