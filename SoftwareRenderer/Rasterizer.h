#ifndef _RASTERIZER_H_
#define _RASTERIZER_H_

#include "IRenderer.h"
#include "Geometry.h"
#include "Model.h"
#include "Camera.h"
#include "Plotter.h"


class Rasterizer : IRenderer
{
	unsigned int _width;
	unsigned int _height;
	unsigned int _bpp;
	int * _zBuffer = nullptr;
	Camera * _camera;
	Plotter * _plotter;
	Model * _currentModel;
	Matrix4d4d _transform;

public:
	bool InterpolateNormals = true;

public:
	Rasterizer(Camera * camera, Plotter * plotter);
	//Rasterizer(unsigned int width, unsigned int height, unsigned int bpp);
	~Rasterizer();
	
	bool RenderModel(Model * model, const Matrix4d4d& viewPort);

	//bool DrawPoly(Vector3d v0, Vector3d v1, Vector3d v2);
	//bool DrawPoly(Vector3d v0, Vector3d v1, Vector3d v2, Vector2d t0, Vector2d t1, Vector2d t2);
	//bool DrawPoly(Vector3d v0, Vector3d v1, Vector3d v2, Vector3d n0, Vector3d n1, Vector3d n2);
	bool DrawPoly(	Vector3d v0, Vector3d v1, Vector3d v2,
					Vector2d t0, Vector2d t1, Vector2d t2,
					Vector3d n0, Vector3d n1, Vector3d n2);

	bool DrawPoly2(	Vector3d v0, Vector3d v1, Vector3d v2,
					Vector2d t0, Vector2d t1, Vector2d t2,
					Vector3d n0, Vector3d n1, Vector3d n2);

	bool DrawLine(Vector3d p0, Vector3d p1, const Texture& color);
	bool DrawLine(double x0, double y0, double x1, double y1, const Texture& color);

	bool Plot(double x, double y, double z, const RgbColor& color);

	inline Plotter * GetPlotter() { return _plotter; }

	void Clear();

private:
	bool DrawScanLine(Vector3d a, Vector3d b, Vector2d ta, Vector2d tb, Vector3d na, Vector3d nb, int y);

};

#endif	//	_RASTERIZER_H_