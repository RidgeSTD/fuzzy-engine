#include <stdio.h>
#include <math.h>
#include "include/svpng.inc"
#include "assets/core.h"
#include "assets/Cube.h"

#define W 512
#define H 512

unsigned char img[W * H * 3];

int main(int argc, char *argv[])
{
    unsigned char *p = img;

    Cube* cube = new Cube();

    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++, p += 3)
        {
            p[0] = (int)((float)x / W * 255.0f);
            p[1] = (int)((float)y / H * 255.0f);
            p[2] = 0;
        }
    }
    svpng(fopen("basic.png", "wb"), W, H, img, 0);

    delete(cube);
    return 0;
}
