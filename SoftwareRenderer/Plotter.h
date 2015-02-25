#ifndef _PLOTTER_H_
#define _PLOTTER_H_

#include <FreeImage.h>
#include "Color.h"
#include <string>
#include "Geometry.h"

class Plotter
{
public:
	Plotter(unsigned int width, unsigned int height, unsigned int bpp);
	~Plotter();

	bool Plot(unsigned int x, unsigned int y, const RgbColor& color);
	bool SaveTo(std::string filename);

	inline unsigned int width() { return _width; }
	inline unsigned int height() { return _height; }
	inline unsigned int bpp() { return _bpp; }

	Matrix4d4d ViewPort;

private:
	Plotter();

	FIBITMAP * _bitmap;
	unsigned int _width;
	unsigned int _height;
	unsigned int _bpp;
	RgbColor _defaultColor;
};

#endif // _PLOTTER_H_