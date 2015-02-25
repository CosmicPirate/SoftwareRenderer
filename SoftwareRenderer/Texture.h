#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Color.h"
#include <string>
#include <FreeImage.h>
#include "Geometry.h"
#include "MathAlgo.h"

class Texture
{
public:
	Texture();
	Texture(const std::string& filename);
	Texture(void* data, int widht, int size);
	~Texture();
	
	FIBITMAP * Load(const std::string& filename);
	virtual RgbColor GetColor(double u, double v) const;

private:
	void * _imageData = nullptr;
	unsigned int _imageWidth = 0;
	unsigned int _imageHeight = 0;
};

#endif // _TEXTURE_H_
