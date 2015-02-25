
#include <GL/freeglut.h>
#include "UserInput.h"

void MouseWheelHandler(int a, int b, int c, int d)
{
	g_eye[0] = 5 * std::cos(g_eye_angle);
	g_eye[2] = 5 * std::sin(g_eye_angle);
	g_eye_angle += b * Deg * 3;
	if (g_eye_angle > 360) g_eye_angle -= 360;
	glutPostRedisplay();
}

void KeyboardHandler(unsigned char ch, int i, int j)
{
	return;
}

void MouseHandler(int a, int b, int c, int d)
{
	return;
}