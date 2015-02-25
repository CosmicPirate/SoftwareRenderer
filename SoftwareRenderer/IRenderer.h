#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Geometry.h"
#include "Model.h"

class IRenderer
{
public:
	virtual ~IRenderer() {  };
	virtual bool RenderModel(Model * model, const Matrix4d4d& viewPort) = 0;
};

#endif // _RENDERER_H_