#include <math.h>
#include <stdio.h>

#include "include/svpng.inc"
#include "assets/Camera.h"
#include "assets/Cube.h"
#include "assets/core.h"

#define W 512
#define H 512


unsigned char img[W * H * 3];

int main(int argc, char *argv[]) {
  unsigned char *p = img;

  Cube *cube = new Cube();

  Camera *camera = new Camera();

  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++, p += 3) {
      p[0] = (int)((float)x / W * 255.0f);
      p[1] = (int)((float)y / H * 255.0f);
      p[2] = 0;
    }
  }
  svpng(fopen("basic.png", "wb"), W, H, img, 0);

  delete (cube);

  return 0;
}
