#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <set>
#include <time.h>

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
	cube->size_ = Vector3f(300, 80, 100);
	scene[0] = cube;
	//cube->set_rotation(Vector3f(M_PI / 4, M_PI / 8, 0));

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
	printf("vertices are in model coordinate as follows:\n");
	for (size_t i = 0; i < num_vertices; i++)
	{
		std::cout << vertices[i] << std::endl;
	}
	Matrix4f V = camera->get_V();
	printf("The vertices are transformed to view coordinate as follows:\n");
	for (size_t i = 0; i < num_vertices; i++) {
		vertices[i] =
			(V * Vector4f(vertices[i].x(), vertices[i].y(), vertices[i].z(), 1.f))
			.block<3, 1>(0, 0);
		std::cout << vertices[i] << std::endl;

	}

	printf("vertex shader finished!\n");

	// ================ PRIMITIVE ASSEMBLY and TESSELATION SHADER
	// ================== fake tesselation for cube
	size_t tesselation_idx[14] = { 3, 2, 6, 7, 4, 2, 0, 3, 1, 6, 5, 4, 1, 0 };

	// GEOMETRY SHADER
	// here we have nothing to do

	// =========================== RESTERIZATION ===========================

	printf("resterization started...\n");

	std::set<int> primitive_set;
	std::vector<FragmentInformation> fragments;

	Vector3f triangle[3];
	float min_y = MAX, max_y = -MAX;
	float min_x = MAX, max_x = -MAX;

	for (size_t i = 2; i < 14; i++) {

		triangle[0] = vertices[tesselation_idx[i - 2]];
		triangle[1] = vertices[tesselation_idx[i - 1]];
		triangle[2] = vertices[tesselation_idx[i]];

		for (size_t j = 0; j < 3; j++)
		{
			for (size_t k = j + 1; k < 3; k++)
			{
				if (triangle[j].x() > triangle[k].x()) {
					std::swap(triangle[j], triangle[k]);
				}
			}
		}

		float x, y;
		for (size_t j = 0; j <= 2; j++) {

			y = triangle[j].y();
			min_y = fmin(y, min_y);
			max_y = fmax(y, max_y);
		}
		printf("start scanning pixelwise vertically...\n");
		std::cout << "scanning range:[" << floor(min_y) << ", " << floor(max_y) << "]" << std::endl;
		for (int v = floor(min_y); v < floor(max_y); v++) {
			min_x = MAX;
			max_x = -MAX;
			x = CalculateXWithPoints(triangle[0], triangle[1], v);
			if (x >= triangle[0].x() && x <= triangle[1].x()) {
				min_x = fmin(min_x, x);
				max_x = fmax(max_x, x);
			}
			x = CalculateXWithPoints(triangle[1], triangle[2], v);
			if (x >= triangle[1].x() && x <= triangle[2].x()) {
				min_x = fmin(min_x, x);
				max_x = fmax(max_x, x);
			}
			x = CalculateXWithPoints(triangle[0], triangle[2], v);
			if (x >= triangle[0].x() && x <= triangle[2].x()) {
				min_x = fmin(min_x, x);
				max_x = fmax(max_x, x);
			}

			if (min_x == MAX || max_x == -MAX) {
				continue;
			}
			printf("start scaning pixelwise horizontally...\n");
			std::cout << "scanning range:[" << floor(min_x) << ", " << floor(max_x) << "]" << std::endl;

			for (int u = floor(min_x); u < floor(max_x); u++) {
				primitive_set.insert(i);
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
	printf("following primitives are resterized\n");
	for (std::set<int>::iterator it = primitive_set.begin(); it != primitive_set.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	// =========================== FRAGMENT SHADER ===========================
	printf("fragment shader started...\n");

	FragmentInformation f;
	int u, v;
	size_t col[36];
	srand((unsigned)time(NULL));
	for (size_t i = 0; i < 36; i++)
	{
		srand(rand());
		col[i] = rand() % 256;
	}
	int col_idx;
	for (size_t i = 0; i < fragments.size(); i++) {
		f = fragments[i];
		u = f.u + W / 2;
		v = f.v + H / 2;
		if (u < 0 || u >= W || v < 0 || v >= H) {
			continue;
		}
		p = buffer + (v * W + u) * 3;
		col_idx = (f.primitive_idx - 1) * 3;
		p[0] = col[col_idx];
		p[1] = col[col_idx + 1];
		p[2] = col[col_idx + 1];
	}

	printf("fragment shader finished!\n");

	return true;
}

float CalculateXWithPoints(Vector3f p1, Vector3f p2, float y) {
	if (abs((p2.y() - p1.y())) < 0.0000001)
		return MAX;
	return p2.x() - (p2.x() - p1.x()) / (p2.y() - p1.y()) * (p2.y() - y);
}
