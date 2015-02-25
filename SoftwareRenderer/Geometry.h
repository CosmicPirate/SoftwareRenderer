#ifndef _VECTOR_3D_
#define _VECTOR_3D_

#include <limits>


#include <glm/glm.hpp>

typedef glm::tvec2<int> Vector2i;
typedef glm::tvec3<int> Vector3i;
typedef glm::tvec4<int> Vector4i;

typedef glm::tvec2<double> Vector2d;
typedef glm::tvec3<double> Vector3d;
typedef glm::tvec4<double> Vector4d;

typedef glm::tmat2x2<float> Matrix2f2f;
typedef glm::tmat3x3<float> Matrix3f3f;
typedef glm::tmat4x4<float> Matrix4f4f;

typedef glm::tmat2x2<double> Matrix2d2d;
typedef glm::tmat3x3<double> Matrix3d3d;
typedef glm::tmat4x4<double> Matrix4d4d;


//template <> gmtl::Vec<int, 3>::Vec(const gmtl::Vec<double, 3> &v);
//template <> gmtl::Vec<double, 3>::Vec(const gmtl::Vec<int, 3> &v);


inline Vector3d cross(Vector3d a, Vector3d b)
{
	return glm::cross(a, b);
}

inline double dot(Vector3d a, Vector3d b)
{
	return glm::dot(a, b);
}

inline Vector2d normalize(Vector2d v)
{
	return glm::normalize(v);
}

inline Vector3d normalize(Vector3d v)
{
	return glm::normalize(v);
}

inline double length(Vector3d v)
{
	return glm::length(v);
}

inline Vector2d interpolate(Vector2d from, Vector2d to, double grad)
{
	return from + (to - from) * grad;
}

inline Vector3d interpolate(Vector3d from, Vector3d to, double grad)
{
	return from + (to - from) * grad;
}

#endif // _VECTOR_3D_