#include "Camera.h"


Camera::Camera(const Vector3d& pos, const Vector3d& dir, const Vector3d& up, bool isLookAt)
			: _position(pos), _up(normalize(up))
{
	_direction = isLookAt ? (dir - pos) : dir;

	CalculateBasis();
	CalculateMatricies();
}


void Camera::LookAt(const Vector3d& pt)
{
	_direction = pt - _position;

	CalculateBasis();
	CalculateMatricies();
}


Camera::~Camera()
{
}


void Camera::CalculateBasis()
{
	_u = normalize(cross(_direction, _up));
	_v = normalize(cross(_direction, _u));
	_w = normalize(cross(_v, _u));
	_center = _position + _direction;
}

void Camera::CalculateMatricies()
{
	//auto tr = Matrix4d4d(
	//	Vector4d(_u, 0),
	//	Vector4d(_v, 0),
	//	Vector4d(_w, 0),
	//	Vector4d(0, 0, 0, 1));

	ViewMatrix = Matrix4d4d(
		Vector4d(_u, 0),
		Vector4d(_v, 0),
		Vector4d(_w, 0),
		Vector4d(0, 0, 0, 1));
				//* Matrix4d4d(
				//	1, 0, 0, 0,
				//	0, 1, 0, 0,
				//	0, 0, 1, 0,
				//	-_center[0], -_center[1], -_center[2], 1);

	Projection = Matrix4d4d(1, 0, 0, 0,
							0, 1, 0, 0,
							0, 0, 1, 0,
							0, -1.0 / length(_direction), 0, 1);
}

