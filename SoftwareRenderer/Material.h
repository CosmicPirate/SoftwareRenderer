#pragma once

#include "Texture.h"
#include "Color.h"

class Material
{
public:
	Material(Texture * texture);
	~Material();

private:
	Texture * _texture;
};

