#include "Rasterizer.h"
#include <ctime>
#include <algorithm>
#include "MathAlgo.h"


//Rasterizer::Rasterizer(unsigned int width, unsigned int height, unsigned int bpp)
//{
//	_plotter = new Plotter(width, height, bpp);
//	_width = width;
//	_height = height;
//	_bpp = bpp;
//	_zBuffer = new double[_width * _height];
//	Clear();
//}

Rasterizer::Rasterizer(Camera * camera, Plotter * plotter)
{
	_camera = camera;
	_plotter = plotter;
	_width = plotter->width();
	_height = plotter->height();
	_bpp - plotter->bpp();
	_zBuffer = new int[_width * _height];
	Clear();
}

Rasterizer::~Rasterizer()
{
	delete _zBuffer;
}

//bool Rasterizer::DrawPoly(	Vector3d v0, Vector3d v1, Vector3d v2,
//							Vector2d t0, Vector2d t1, Vector2d t2,
//							Vector3d n0, Vector3d n1, Vector3d n2)
//{
//	if (v0[1] == v1[1] && v0[1] == v2[1]) return false;
//
//	Vector3d normal = normalize(cross(v2 - v0, v1 - v0));
//
//	if (v0[1] > v1[1] || (v0[1] == v1[1] && v0[0] < v1[0])) { std::swap(v0, v1); std::swap(t0, t1); }
//	if (v0[1] > v2[1] || (v0[1] == v2[1] && v0[0] < v2[0])) { std::swap(v0, v2); std::swap(t0, t2); }
//	if (v1[1] > v2[1] || (v1[1] == v2[1] && v1[0] < v2[0])) { std::swap(v1, v2); std::swap(t1, t2); }
//
//	Vector3d
//		adir = v1 - v0,
//		bdir = v2 - v0,
//		cdir = v2 - v1;
//	Vector3d
//		astep = (int)adir[1] != 0 ? (adir / std::floor(adir[1])) : adir,
//		bstep = (int)bdir[1] != 0 ? (bdir / std::floor(bdir[1])) : bdir,
//		cstep = (int)cdir[1] != 0 ? (cdir / std::floor(cdir[1])) : cdir;
//	Vector2d
//		tadir = t1 - t0,
//		tbdir = t2 - t0,
//		tcdir = t2 - t1;
//	Vector2d
//		tastep = (int)adir[1] != 0 ? (tadir / std::floor(adir[1])) : tadir,
//		tbstep = (int)bdir[1] != 0 ? (tbdir / std::floor(bdir[1])) : tbdir,
//		tcstep = (int)cdir[1] != 0 ? (tcdir / std::floor(cdir[1])) : tcdir;
//
//	Vector3d
//		a = v0,
//		b = a;
//	Vector2d
//		ta = t0,
//		tb = ta;
//
//	for (int y = v0[1]; y <= /*frac(v2[1]) < 0.5 ? (int)v2[1] - 1 : */v2[1]; ++y)
//	{
//		int steps = b[0] - a[0];
//		double zstep = steps != 0 ? ((b[2] - a[2]) / steps) : (b[2] - a[2]);
//		Vector2d tdir = tb - ta;
//		Vector2d tstep = steps != 0 ? (tdir / (double)steps) : tdir;
//		if (a[0] < b[0]) {
//			double z = a[2];
//			Vector2d tp(ta);
//			for (int x = a[0]; x <= std::floor(b[0]); ++x) {
//				z += zstep; tp += tstep;
//				RgbColor color;
//				if (_currentModel->Diffuse(tp[0], tp[1], normal, color, _transform))
//					Plot(x, y, z, color);
//			}
//		} else {
//			double z = b[2];
//			Vector2d tp(tb);
//			for (int x = b[0]; x <= std::floor(a[0]); ++x) {
//				z += zstep; tp += tstep;
//				RgbColor color;
//				if (_currentModel->Diffuse(tp[0], tp[1], normal, color, _transform))
//					Plot(x, y, z, color);
//			}
//		}
//
//		if (y > v1[1]) {
//			a += cstep; ta += tcstep;
//			if ((cstep[0] > 0 && a[0] > v2[0]) ||
//				(cstep[0] < 0 && a[0] < v2[0]))	a = v2;
//			if ((tcstep[0] > 0 && ta[0] > t2[0]) ||
//				(tcstep[0] < 0 && ta[0] < t2[0]))	ta = t2;
//		} else {
//			a += astep; ta += tastep;
//			if ((astep[0] > 0 && a[0] > v1[0]) ||
//				(astep[0] < 0 && a[0] < v1[0]))	a = v1;
//			if ((tastep[0] > 0 && ta[0] > t1[0]) ||
//				(tastep[0] < 0 && ta[0] < t1[0]))	ta = t1;
//		}
//
//		b += bstep; tb += tbstep;
//		if ((bstep[0] > 0 && b[0] > v2[0]) ||
//			(bstep[0] < 0 && b[0] < v2[0]))	b = v2;
//		if ((tbstep[0] > 0 && tb[0] > t2[0]) ||
//			(tbstep[0] < 0 && tb[0] < t2[0]))	tb = t2;
//	}
//
//	return true;
//}

bool Rasterizer::DrawPoly(	Vector3d v0, Vector3d v1, Vector3d v2,
							Vector2d t0, Vector2d t1, Vector2d t2,
							Vector3d n0, Vector3d n1, Vector3d n2)
{
	if (v0[1] == v1[1] && v0[1] == v2[1]) return false;

	if (v0[1] > v1[1]/* || (v0[1] == v1[1] && v0[0] < v1[0])*/) { std::swap(v0, v1); std::swap(t0, t1); std::swap(n0, n1); }
	if (v0[1] > v2[1]/* || (v0[1] == v2[1] && v0[0] < v2[0])*/) { std::swap(v0, v2); std::swap(t0, t2); std::swap(n0, n2); }
	if (v1[1] > v2[1]/* || (v1[1] == v2[1] && v1[0] < v2[0])*/) { std::swap(v1, v2); std::swap(t1, t2); std::swap(n1, n2); }

	Vector3d
		adir = v2 - v0,	//	длинная
		bdir = v1 - v0,	//	первая короткая
		cdir = v2 - v1;	//	вторая короткая

	double aGradStep = 1 / adir[1];
	double aGrad = 0;
	double bGradStep = 1 / bdir[1];
	double bGrad = 0;
	double cGradStep = 1 / cdir[1];
	double cGrad = 0;

	Vector3d a, b;
	Vector2d ta, tb;
	Vector3d na, nb;
	
	if (!InterpolateNormals)
		na = nb = normalize(cross(bdir, adir));

	//for (int y = std::round(v0[1]); y < std::round(v2[1]); ++y) {
	for (int y = v0[1]; y < v2[1]; ++y) {
		a = interpolate(v0, v2, aGrad);
		ta = interpolate(t0, t2, aGrad);
		if (InterpolateNormals)
			na = interpolate(n0, n2, aGrad);
		
		if (y < v1[1])
		{
			b = interpolate(v0, v1, bGrad);
			tb = interpolate(t0, t1, bGrad);
			if (InterpolateNormals)
				nb = interpolate(n0, n1, bGrad);
			bGrad += bGradStep;
			bGrad = math_algo::clamp(bGrad);
		} else {
			b = interpolate(v1, v2, cGrad);
			tb = interpolate(t1, t2, cGrad);
			if (InterpolateNormals)
				nb = interpolate(n1, n2, cGrad);
			cGrad += cGradStep;
			cGrad = math_algo::clamp(cGrad);
		}
		aGrad += aGradStep;
		aGrad = math_algo::clamp(aGrad);

		if (!DrawScanLine(a, b, ta, tb, na, nb, y))
			return false;
	}

	return true;
}

bool Rasterizer::DrawScanLine(Vector3d a, Vector3d b, Vector2d ta, Vector2d tb, Vector3d na, Vector3d nb, int y)
{
	if (a[0] > b[0]) { std::swap(a, b); std::swap(ta, tb); std::swap(na, nb); }

	Vector3d dir = b - a;
	double gradStep = 1 / dir[0];
	double grad = 0;
	Vector3d p, np = na;
	Vector2d tp;
	//for (int x = std::round(a[0])-1; x < std::round(b[0])-1; ++x, grad += gradStep) {
	for (int x = a[0]; x < b[0]; ++x, grad+=gradStep) {
		p = interpolate(a, b, grad);
		tp = interpolate(ta, tb, grad);
		if (InterpolateNormals)
			np = interpolate(na, nb, grad);

		RgbColor color;
		if (_currentModel->Diffuse(tp[0], tp[1], normalize(np), color, _transform))
			Plot(x, y, p[2], color);
	}

	return true;
}

bool Rasterizer::DrawLine(Vector3d p0, Vector3d p1, const Texture& color)
{
	return DrawLine(p0[0], p0[1], p1[0], p1[1], color);
}

bool Rasterizer::DrawLine(double x0, double y0, double x1, double y1, const Texture& color)
{
	double dx = std::abs(x1 - x0), dy = std::abs(y1 - y0);
	double tmp;
	if (y0 > y1) {
		tmp = y0; y0 = y1; y1 = tmp;
		tmp = x0; x0 = x1; x1 = tmp;
	}

	if (dx < dy) {
		float r = x0 < x1 ? dx / dy : -dx / dy;
		float x = x0;
		if (y0 > y1) {
			std::swap(y0, y1);
			x = x1; r = -r;
		}
		for (int y = y0; y < y1; ++y, x += r) {
			Plot(x, y, 0, color.GetColor(0, 0));
		}
	} else {
		float r = y0 < y1 ? dy / dx : -dy / dx;
		float y = y0;
		if (x0 > x1) {
			std::swap(x0, x1);
			y = y1; r = -r ;
		}
		for (int x = x0; x < x1; ++x, y += r) {
			Plot(x, y, 0, color.GetColor(0, 0));
		}
	}
	return true;
}

bool Rasterizer::Plot(double x, double y, double z, const RgbColor& color)
{
	x = (int)x; y = (int)y; z = (int)z;
	if (x >= _width || y >= _height)
		return false;

	unsigned int ind = x + y * _width;
	if (z - _zBuffer[ind] > 1) {
		_zBuffer[ind] = z;

		_plotter->Plot(x, y, color);

		return true;
	}

	return false;
}

bool Rasterizer::RenderModel(Model * model, const Matrix4d4d& viewPort)
{
	std::srand(std::time(NULL));

	_currentModel = model;
	_transform = viewPort * /*_camera->Projection **/ _camera->ViewMatrix;

	for (auto it = model->Faces().begin(); it != model->Faces().end(); ++it)
	{
		Matrix4d4d normalTransform = glm::inverse(glm::transpose(_transform));
		Vector3d v[3], n[3], screenV[3], screenN[3];
		Vector2d t[3];
		bool hasTCoords = model->TextureCoords().size() > 0;
		bool hasNormals = model->Normals().size() > 0;
		for (int i = 0; i < 3; ++i) {
			v[i] = model->Vertices()[it->vertIndexes[i]];
			screenV[i] = Vector3d(_transform * Vector4d(v[i], 1));
			if (hasNormals) {
				n[i] = model->Normals()[it->normIndexes[i]];
				screenN[i] = normalize(Vector3d(normalTransform * Vector4d(n[i], 0)));
			}
			if (hasTCoords)
				t[i] = model->TextureCoords()[it->textPosIndexes[i]];
		}

		DrawPoly(screenV[0], screenV[1], screenV[2], t[0], t[1], t[2], screenN[0], screenN[1], screenN[2]);
		//DrawPoly2(screenV[0], screenV[1], screenV[2], t[0], t[1], t[2], screenN[0], screenN[1], screenN[2]);
	}

	Clear();
	return true;
}

void Rasterizer::Clear()
{
	memset(_zBuffer, -std::numeric_limits<int>::min(), _width * _height);
}
