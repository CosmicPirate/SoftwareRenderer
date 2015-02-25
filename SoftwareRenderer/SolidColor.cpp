#include "SolidColor.h"


SolidColor::SolidColor(RgbColor color)
{
	_color = RgbColor(color);
}

SolidColor::SolidColor(unsigned char * color, int channels)
{
	_color = RgbColor();

	if (channels < 3) throw "not enugh channels";
	if (channels == 3)
	{
		_color[0] = color[0];
		_color[1] = color[1];
		_color[2] = color[2];
	}
	if (channels > 3)
		_color[3] = color[3];
}

SolidColor::~SolidColor()
{
}


RgbColor SolidColor::GetColor(double u, double v) const
{
	return _color;
}