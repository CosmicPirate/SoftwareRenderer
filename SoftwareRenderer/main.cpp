
#include <iostream>
#include <ctime>

#include "Rasterizer.h"
#include "ObjParser.h"
#include "Texture.h"
#include "SolidColor.h"
#include "Camera.h"
#include "Plotter.h"
#include "Geometry.h"

#define _USE_MATH_DEFINES
#include <math.h>

unsigned char color[3][3] = { { 255, 0, 0 },
							{ 0, 255, 0 },
							{ 0, 0, 255 }
							};

void PolyTest(Rasterizer * rend, Matrix4d4d viewPort);
void LineTest(Rasterizer * rend, Matrix4d4d viewPort);
Matrix4d4d Viewport(int x, int y, int w, int h);

const int	width = 800,
			height = 800,
			bpp = 24,
			depth = 255;

int main(int argc, char *argv[])
{
	Model * model = ObjParser::Parse("obj\\african_head.obj");
	//Model * model = ObjParser::Parse("obj\\cube.obj");
	
	Texture texture;
	texture.Load("obj\\african_head_diffuse.tga");
	
	//RgbColor color(255, 255, 0);
	//SolidColor texture(color);

	model->SetTexture(&texture);
	model->AddDirectedLight(Vector3d(1, 0, 1));

	Camera cam(Vector3d(0, 0, 5), Vector3d(0, 0, 0), Vector3d(0, 1.0, 0), true);
	Plotter plotter(width, height, bpp);
	Rasterizer rend(&cam, &plotter);

	rend.InterpolateNormals = false;
	Matrix4d4d viewPort = Viewport(width / 8, height / 8, width*3/4, height*3/4);
	rend.RenderModel(model, viewPort);
	
	//PolyTest(&rend);
	//LineTest(&rend);

	bool success = plotter.SaveTo("output.bmp");

	return 0;
}

Matrix4d4d Viewport(int x, int y, int w, int h) {
	Matrix4d4d m = Matrix4d4d(1);
	m[3][0] = x + w / 2.f;
	m[3][1] = y + h / 2.f;
	m[3][2] = depth / 2.f;

	m[0][0] = w / 2.f;
	m[1][1] = h / 2.f;
	m[2][2] = depth / 2.f;
	return m;
}

void PolyTest(Rasterizer * rend, Matrix4d4d viewPort)
{
	Model * triangles = new Model();
	unsigned char randColor[3] = { std::rand(), std::rand(), std::rand() };
	SolidColor texture(randColor, 3);
	triangles->SetTexture(&texture);

	std::srand(std::time(NULL));

	Vector3d center(400, 400, 0);
	triangles->AddVertex(center);
	int ind = 1;
	for (int i = 0; i < 360; i += 10)
	{
		double angle = i *(M_PI / 180);
		double angle2 = (i + 5) *(M_PI / 180);
		double x = std::cos(angle) * center[0];
		double y = std::sin(angle) * center[1];
		double x1 = std::cos(angle2) * center[0];
		double y1 = std::sin(angle2) * center[1];
		triangles->AddVertex(Vector3d(x + center[0], y + center[1], 0));
		triangles->AddVertex(Vector3d(x1 + center[0], y1 + center[1], 0));
		triangles->AddFace(Face{ { 0, ind++, ind++ }, { 0, 0, 0 }, { 0, 0, 0 } });
	}

	triangles->AddTextureCoord(0, 0);
	triangles->AddDirectedLight(Vector3d(0, 0, -1));

	rend->RenderModel(triangles, viewPort);
}


void LineTest(Rasterizer * rend, Matrix4d4d viewPort)
{
	std::srand(std::time(NULL));
	Vector3d center(400, 400, 0);
	for (int i = 0; i < 360; ++i)
	{
		double angle = i *(3.14 / 180);
		double x = std::cos(angle) * center[0];
		double y = std::sin(angle) * center[1];
		unsigned char randColor[3] = { std::rand(), std::rand(), std::rand() };
		SolidColor texture(randColor, 3);
		rend->DrawLine(center, Vector3d(x + center[0], y + center[1], 0), texture);
	}
}
