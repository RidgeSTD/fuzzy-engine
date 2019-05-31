#ifndef CORE_H
#define CORE_H
    struct Vector3 {
        float x, y, z;
        Vector3(float x, float y, float z){
            this->x = x;
            this->y = y;
            this->z = z;
        };
        Vector3(){
            this->x = 0;
            this->y = 0;
            this->z = 0;
        }
    };
#endif // CORE_H