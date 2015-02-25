#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <GL/freeglut.h>
#include "../SoftwareRenderer/Texture.h"
#include "../SoftwareRenderer/Model.h"
#include "../SoftwareRenderer/ObjParser.h"
#include "../SoftwareRenderer/Camera.h"

#include "UserInput.h"

Camera * g_currentCamera;
Model * g_currentModel;
int g_width, g_height;

Vector3d g_eye;
double g_eye_angle = 0;

void RenderModel(Model * model);
void Display();

void ReshapeWindow(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, (float)w / (float)h, 2.0, 200.0);
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 200.0);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(g_eye[0], g_eye[1], g_eye[2], 0, 0, 0, 0, -1, 0);

	GLfloat light_position[] = { 0.0, 10.0, 0.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glColor3f(0, 0, 1.0);

	RenderModel(g_currentModel);

	glFlush();
	glutSwapBuffers();
}

void RenderModel(Model * model)
{
	if (model->Normals().size() > 0) {
		glNormalPointer(GL_DOUBLE, sizeof(Vector3d), model->Normals().data());
	}

	//if (model->TextureCoords().size() > 0) {
	//	glTexCoordPointer(2, GL_DOUBLE, sizeof(Vector2d), model->TextureCoords().data());
	//}

	glVertexPointer(3, GL_DOUBLE, /*sizeof(Vector3d)*/0, model->Vertices().data());

	glDrawElements(GL_TRIANGLES, model->VertIndices().size(), GL_UNSIGNED_INT, model->VertIndices().data());
	//glDrawArrays(GL_TRIANGLES, 0, model->Vertices().size());

	//glBegin(GL_TRIANGLES);
	//for (auto face = g_currentModel->Faces().begin(); face != g_currentModel->Faces().end(); ++face)
	//{
	//	for (int i = 0; i < 3; ++i) {
	//		auto v = g_currentModel->Vertices()[face->vertIndexes[i]];
	//		//auto n = g_currentModel->Normals()[face->normIndexes[i]];
	//		//auto uv = g_currentModel->TextureCoords()[face->textPosIndexes[i]];
	//		glVertex3d(v[0], v[1], v[2]);
	//		//glNormal3d(n[0], n[1], n[2]);
	//		//glTexCoord2f(uv[0], uv[1]);
	//	}
	//}
	//glEnd();
}

void initGlut(int * pargc, char ** argv, int width, int height)
{
	glutInit(pargc, argv);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutCreateWindow("Model Viewr");

	glutKeyboardFunc(KeyboardHandler);
	glutMouseFunc(MouseHandler);
	glutDisplayFunc(Display);
	glutReshapeFunc(ReshapeWindow);
	glutMouseWheelFunc(MouseWheelHandler);

	g_width = width; g_height = height;
}

void oglInit()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);

	glEnable(GL_NORMALIZE);

	//	lighting
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat red_light[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };

	glShadeModel(GL_SMOOTH);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, red_light);
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	//

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//glPolygonMode(GL_FRONT, GL_FILL);
	//glPolygonMode(GL_BACK, GL_LINE);
}

void loadModel(std::string filename, std::string textureFile = "")
{
	Model * model = ObjParser::Parse(filename);

	Texture texture;
	if (textureFile.length() > 0) {
		texture.Load(textureFile);
	}

	model->SetTexture(&texture);
	model->AddDirectedLight(Vector3d(1, 0, 1));

	g_currentModel = model;
}

int main(int argc, char ** argv)
{
	initGlut(&argc, argv, 800, 600);
	oglInit();

	loadModel("obj\\african_head.obj", "obj\\african_head_diffuse.tga");
	//loadModel("obj\\teapot.obj");

	g_eye = Vector3d(5, -1.5, 5);

	glutMainLoop();
	return EXIT_SUCCESS;
}
