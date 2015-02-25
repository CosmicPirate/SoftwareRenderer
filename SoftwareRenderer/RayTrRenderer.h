#ifndef _RAYTRRENDERER_H_
#define _RAYTRRENDERER_H_

#include "IRenderer.h"
#include "Camera.h"
#include "Plotter.h"

class RayTrRenderer : IRenderer
{
public:
	RayTrRenderer(Camera * camera, Plotter * plotter);
	~RayTrRenderer();

	bool RenderModel(Model * model, const Matrix4d4d& viewPort);
};

#endif // _RAYTRRENDERER_H_