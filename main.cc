#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>

#include "assets/Camera.h"
#include "assets/Cube.h"
#include "assets/Object3D.h"
#include "assets/core.h"
#include "include/svpng.inc"

#define W 512
#define H 512
#define MAX 999999999

using namespace Eigen;

unsigned char img[W * H * 3];
bool RunRenderPipeline(Camera *camera, Object3D **objects,
                       unsigned char *buffer);
float CalculateXWithPoints(Vector3f p1, Vector3f p2, float y);

struct FragmentInformation {
  // Vector3f position;
  int u, v;
  int primitive_idx; // for coloring
};

int main(int argc, char *argv[]) {
  Object3D *scene[1];

  Cube *cube = new Cube();
  cube->size_ = Vector3f(5, 5, 5);
  scene[0] = cube;

  Camera *camera = new Camera();

  camera->position_ = Vector3f(0, 0, -5);

  printf("start render...\n");

  RunRenderPipeline(camera, scene, img);

  svpng(fopen("basic.png", "wb"), W, H, img, 0);
  delete (cube);

  printf("program ended successfully!\n");
  return 0;
}

bool RunRenderPipeline(Camera *camera, Object3D **objects,
                       unsigned char *buffer) {
  unsigned char *p = buffer;

  Vector3f *vertices = objects[0]->get_vertices();
  int num_vertices = objects[0]->get_num_vertices();

  // =========================== DRAW BACKGROUND ===========================
  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++, p += 3) {
      p[0] = p[1] = p[2] = 0;
    }
  }
  printf("draw background finished!\n");

  // =========================== VERTEX SHADER ===========================
  Matrix4f V = camera->get_V();
  for (size_t i = 0; i < num_vertices; i++) {
    vertices[i] =
        (V * Vector4f(vertices[i].x(), vertices[i].y(), vertices[i].z(), 1.f))
            .block<3, 1>(0, 0);
  }

  std::cout << vertices << std::endl;
  printf("vertex shader finished!\n");

  // ================ PRIMITIVE ASSEMBLY and TESSELATION SHADER
  // ================== fake tesselation for cube
  size_t tesselation_idx[14] = {1, 2, 3, 6, 7, 5, 8, 4, 3, 7, 6, 5, 2, 1};

  // GEOMETRY SHADER
  // here we have nothing to do

  // =========================== RESTERIZATION ===========================

  printf("resterization started...\n");

  std::vector<FragmentInformation> fragments;
  for (size_t i = 2; i < 14; i++) {

    int left, up, down;
    float min = MAX, max = -MAX;
    float x, y;
    for (size_t j = i - 2; j <= i; j++) {
      x = vertices[tesselation_idx[j]].x();
      if (x < min) {
        min = x;
        left = j;
      }
    }
    up = down = -1;
    for (size_t j = i - 2; j <= i; j++) {
      if (j == left)
        continue;
      if (up < 0)
        up = j;
      else
        down = j;
    }
    left = tesselation_idx[left];
    up = tesselation_idx[up];
    down = tesselation_idx[down];

    if (vertices[up].y() < vertices[down].y()) {
      std::swap(up, down);
    }
    printf("start scanning pixelwise...\n");
    std::cout << "scanning range:[" << (int)vertices[down].y() << ", " << (int)vertices[up].y() << "]" << std::endl;
    for (int v = (int)(vertices[down].y() + 0.5); v < (int)(vertices[up].y()); v++) {
      min = MAX;
      max = -MAX;
      x = CalculateXWithPoints(vertices[left], vertices[up], v);
      if (x >= vertices[left].x() && x <= vertices[up].x()) {
        min = fmin(min, x);
        max = fmax(max, x);
      }
      x = CalculateXWithPoints(vertices[left], vertices[down], v);
      if (x >= vertices[left].x() && x <= vertices[down].x()) {
        min = fmin(min, x);
        max = fmax(max, x);
      }
      x = CalculateXWithPoints(vertices[down], vertices[up], v);
      if (x >= vertices[down].x() && x <= vertices[up].x()) {
        min = fmin(min, x);
        max = fmax(max, x);
      }

      printf("start scaning horizontal...\n");
    std::cout << "scanning range:[" << min << ", " << max << "]" << std::endl;

      for (int u = min; u < max; u++) {
        FragmentInformation fi;
        fi.u = u;
        fi.v = v;
        fi.primitive_idx = i;
        fragments.push_back(fi);
      }
    }
    std::cout << "primitive " << i << " resterized" << std::endl;
  }
  printf("resterization finished!\n");
  // =========================== FRAGMENT SHADER ===========================
  printf("fragment shader started...\n");

  FragmentInformation f;
  int u, v;
  for (size_t i = 0; i < fragments.size(); i++) {
    f = fragments[i];
    u = f.u + W / 2;
    v = f.v + H / 2;
    if (u < 0 || u >= W || v < 0 || v >= H) {
      continue;
    }
    p = buffer + (v * W + u) * 3;
    p[0] = (int)((float)f.primitive_idx / 14.f * 255);
  }

  printf("fragment shader finished!\n");

  return true;
}

float CalculateXWithPoints(Vector3f p1, Vector3f p2, float y) {
  if (abs((p2.y() - p1.y())) < 0.0000001)
    return MAX;
  return p2.x() - (p2.x() - p1.x()) / (p2.y() - p1.y()) * (p2.y() - y);
}
