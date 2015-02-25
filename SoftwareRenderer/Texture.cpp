#include "Texture.h"

Texture::Texture()
{
	_imageData = nullptr;
}

Texture::Texture(const std::string& filename)
{
	_imageData = Load(filename);
}

Texture::~Texture()
{
	//if (_imageData != nullptr)
	//	delete _imageData;
}

FIBITMAP * Texture::Load(const std::string& filename)
{
	try {
		// TODO: сделать для остальных форматов
		auto img = FreeImage_Load(FIF_TARGA, filename.c_str());
		_imageData = img;
		_imageWidth = FreeImage_GetWidth(img);
		_imageHeight = FreeImage_GetHeight(img);
		return (FIBITMAP *)_imageData;
	}
	catch (std::exception ex)
	{
		return nullptr;
	}
}

RgbColor Texture::GetColor(double u, double v) const
{
	int iu = (std::abs(u) <= 1) ? u * _imageWidth : math_algo::sgn(u) * _imageWidth - 1;
	int iv = (std::abs(v) <= 1) ? v * _imageHeight : math_algo::sgn(v) * _imageHeight - 1;
	RGBQUAD quad;
	bool success = FreeImage_GetPixelColor((FIBITMAP*)_imageData, iu, iv, &quad);
	RgbColor ret = RgbColor();
	ret[0] = quad.rgbRed;
	ret[1] = quad.rgbGreen;
	ret[2] = quad.rgbBlue;
	return ret;
}
