#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#define _USE_MATH_DEFINES
#include <cmath>
#include "../SoftwareRenderer/Geometry.h"

class Model;
class Camera;

extern Camera * g_currentCamera;
extern Model * g_currentModel;
extern int g_width, g_height;

extern Vector3d g_eye;
extern double g_eye_angle;
const double Deg = M_PI / 180;

#endif // _GLOBALS_H_