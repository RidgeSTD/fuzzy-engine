#include <math.h>
#include <stdio.h>
#include <Eigen/Dense>
#include <iostream>

#include "include/svpng.inc"
#include "assets/Camera.h"
#include "assets/Cube.h"
#include "assets/core.h"

#define W 512
#define H 512

using Eigen::MatrixXd;

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

  printf("eigen part starts\n");
  MatrixXd m(2,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);
  std::cout << m << std::endl;
  printf("eigen part ends\n");
  return 0;
}
