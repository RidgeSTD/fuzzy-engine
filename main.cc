#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <set>
#include <time.h>

#include "core/Camera.h"
#include "core/Cube.h"
#include "core/ArbitraryObject3D.h"
#include "core/Object3D.h"
#include "core/common_include.h"
#include "include/svpng.inc"
#include "include/igl/readOBJ.h"

#define W 512
#define H 512
#define MAX 999999999

using namespace Eigen;

unsigned char img[W * H * 3];
bool RunRenderPipeline(Camera *camera, Object3D **objects,
	unsigned char *buffer);
float CalculateXWithPoints(Vector3f p1, Vector3f p2, float y);

struct FragmentInformation
{
	// Vector3f position;
	int u, v;
	int primitive_idx; // for coloring
};

int main(int argc, char *argv[])
{
	Object3D *scene[1];

	ArbitraryObject3D* obj = new ArbitraryObject3D("assets\\stanford_bunny.obj");
	obj->set_scale(Vector3f(1500, 1500, 1500));
	scene[0] = obj;
	obj->set_position(Vector3f(0, 200, 0));
	obj->set_rotation(Vector3f(0, 0, M_PI));


	Camera *camera = new Camera();

	camera->position_ = Vector3f(0, 0, -5);
	//Quaternion<float> q = AngleAxisf(M_PI / 3, Vector3f::UnitX()) * AngleAxisf(-M_PI / 4, Vector3f::UnitY()) * AngleAxisf(M_PI / 3, Vector3f::UnitZ());
	//camera->rotate(q.matrix());

	printf("start render...\n");

	RunRenderPipeline(camera, scene, img);

	svpng(fopen("basic.png", "wb"), W, H, img, 0);
	delete (obj);

	printf("program ended successfully!\n");
	return 0;
}

bool RunRenderPipeline(Camera *camera, Object3D **objects,
	unsigned char *buffer)
{
	unsigned char *p = buffer;

	// =========================== DRAW BACKGROUND ===========================
	for (int y = 0; y < H; y++)
	{
		for (int x = 0; x < W; x++, p += 3)
		{
			p[0] = p[1] = p[2] = 0;
		}
	}
	printf("draw background finished!\n");

	// =========================== VERTEX SHADER ===========================
	MatrixXf vertices = objects[0]->get_vertices();
	int num_vertices = objects[0]->get_num_vertices();

	std::cout << num_vertices << "vertices loaded!" << std::endl;
	Matrix4f V = camera->get_V();
	{
		Vector4f _v;
		Vector3f _v3;
		for (size_t i = 0; i < num_vertices; i++)
		{
			_v3 = vertices.row(i);
			_v << _v3, 1.f;
			_v3 = (V * _v).head(3);
			vertices.row(i) = _v3;
		}
	}
	printf("The vertices are transformed to view coordinate\n");
	printf("vertex shader finished!\n");

	// ================ PRIMITIVE ASSEMBLY and TESSELATION SHADER ================
	// fake tesselation for cube
	MatrixXf faces = objects[0]->get_faces();

	// ================ GEOMETRY SHADER ================
	// here we have nothing to do

	// =========================== RESTERIZATION ===========================

	printf("resterization started...\n");

	std::vector<FragmentInformation> fragments;

	Vector3f triangle[3];
	float min_y = MAX, max_y = -MAX;
	float min_x = MAX, max_x = -MAX;

	for (size_t i = 0; i < faces.rows(); i++)
	{
		triangle[0] = Vector3f(vertices.row(faces(i, 0)));
		triangle[1] = Vector3f(vertices.row(faces(i, 1)));
		triangle[2] = Vector3f(vertices.row(faces(i, 2)));

		for (size_t j = 0; j < 3; j++)
		{
			for (size_t k = j + 1; k < 3; k++)
			{
				if (triangle[j].x() > triangle[k].x())
				{
					std::swap(triangle[j], triangle[k]);
				}
			}
		}

		float x, y;
		for (size_t j = 0; j <= 2; j++)
		{

			y = triangle[j].y();
			min_y = fmin(y, min_y);
			max_y = fmax(y, max_y);
		}
		//printf("start scanning pixelwise vertically...\n");
		//std::cout << "scanning range:[" << floor(min_y) << ", " << floor(max_y) << "]" << std::endl;
		for (int v = floor(min_y); v < floor(max_y); v++)
		{
			min_x = MAX;
			max_x = -MAX;
			x = CalculateXWithPoints(triangle[0], triangle[1], v);
			if (x >= triangle[0].x() && x <= triangle[1].x())
			{
				min_x = fmin(min_x, x);
				max_x = fmax(max_x, x);
			}
			x = CalculateXWithPoints(triangle[1], triangle[2], v);
			if (x >= triangle[1].x() && x <= triangle[2].x())
			{
				min_x = fmin(min_x, x);
				max_x = fmax(max_x, x);
			}
			x = CalculateXWithPoints(triangle[0], triangle[2], v);
			if (x >= triangle[0].x() && x <= triangle[2].x())
			{
				min_x = fmin(min_x, x);
				max_x = fmax(max_x, x);
			}

			if (min_x == MAX || max_x == -MAX)
			{
				continue;
			}
			//printf("start scaning pixelwise horizontally...\n");
			//std::cout << "scanning range:[" << floor(min_x) << ", " << floor(max_x) << "]" << std::endl;

			for (int u = floor(min_x); u < floor(max_x); u++)
			{
				FragmentInformation fi;
				fi.u = u;
				fi.v = v;
				fi.primitive_idx = i;
				fragments.push_back(fi);
			}
		}
	}
	printf("resterization finished!\n");

	// =========================== FRAGMENT SHADER ===========================
	printf("fragment shader started...\n");

	FragmentInformation f;
	int u, v;
	size_t* col = (size_t*)malloc(sizeof(size_t) * faces.rows() * 3);
	srand((unsigned)time(NULL));
	for (size_t i = 0; i < 36; i++)
	{
		srand(rand());
		col[i] = rand() % 256;
	}
	int col_idx;
	for (size_t i = 0; i < fragments.size(); i++)
	{
		f = fragments[i];
		u = f.u + W / 2;
		v = f.v + H / 2;
		if (u < 0 || u >= W || v < 0 || v >= H)
		{
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

float CalculateXWithPoints(Vector3f p1, Vector3f p2, float y)
{
	if (abs((p2.y() - p1.y())) < 0.0000001)
		return MAX;
	return p2.x() - (p2.x() - p1.x()) / (p2.y() - p1.y()) * (p2.y() - y);
}
