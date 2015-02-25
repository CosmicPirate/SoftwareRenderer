#include "Plotter.h"


Plotter::Plotter()
{
	FreeImage_Initialise();
}

Plotter::Plotter(unsigned int width, unsigned int height, unsigned int bpp) : Plotter()
{
	_bitmap = FreeImage_Allocate(width, height, bpp);
	if (_bitmap != 0) {
		_width = width;
		_height = height;
		_bpp = bpp;
	}
	//RGBQUAD red;
	//red.rgbBlue = 0;
	//red.rgbRed = 255;
	//red.rgbGreen = 0;
	//FreeImage_FillBackground(_bitmap, &red);
}


Plotter::~Plotter()
{
}


bool Plotter::Plot(unsigned int x, unsigned int y, const RgbColor& color)
{
	if (x >= _width || y >= _height) return false;

	RGBQUAD quad;
	quad.rgbBlue = color[2];
	quad.rgbGreen = color[1];
	quad.rgbRed = color[0];
	FreeImage_SetPixelColor(_bitmap, x, y, &quad);

	//auto fif = FreeImage_GetFIFFromFilename("debug.bmp");
	//FreeImage_Save(fif, _bitmap, "debug.bmp");

	return true;
}

bool Plotter::SaveTo(std::string filename)
{
	//FreeImage_FlipVertical(_bitmap);
	auto fif = FreeImage_GetFIFFromFilename(filename.c_str());
	return FreeImage_Save(fif, _bitmap, filename.c_str());
}