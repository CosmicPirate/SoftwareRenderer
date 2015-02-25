#pragma once

#include "Texture.h"

class SolidColor :
	public Texture
{
public:
	SolidColor(RgbColor color);
	SolidColor(unsigned char * color, int channels);
	~SolidColor();

	virtual RgbColor GetColor(double u, double v) const;

private:
	RgbColor _color;
};

