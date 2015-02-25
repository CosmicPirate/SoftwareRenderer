#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Geometry.h"

class Camera
{
	Vector3d _position;
	Vector3d _direction;
	Vector3d _up;
	Vector3d _center;
	Vector3d _u, _v, _w;

public:
	Camera(const Vector3d& pos, const Vector3d& dir, const Vector3d& up, bool isLookAt = false);
	~Camera();

	void LookAt(const Vector3d& pt);

	Matrix4d4d ViewMatrix;
	Matrix4d4d Projection;

private:
	void CalculateBasis();
	void CalculateMatricies();
};

#endif // _CAMERA_H_