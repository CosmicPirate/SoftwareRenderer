#ifndef _MODEL_H_
#define _MODEL_H_

#include "Color.h"
#include "Texture.h"
#include <fstream>
#include <vector>

struct Face
{
	unsigned int size;
	unsigned int * vertIndexes;
	unsigned int * normIndexes;
	unsigned int * textPosIndexes;
};


class Model
{
public:
	Model()
	{
		ModelMatrix = Matrix4d4d(1.0);
	}

	void AddVertex(const Vector3d& vertex)
	{
		_vertices.push_back(vertex);
		if (Maximum[0] < vertex[0])
			Maximum[0] = vertex[0];
		if (Maximum[1] < vertex[1])
			Maximum[1] = vertex[1];
		if (Maximum[2] < vertex[2])
			Maximum[2] = vertex[2];

		if (Minimum[0] > vertex[0])
			Minimum[0] = vertex[0];
		if (Minimum[1] > vertex[1])
			Minimum[1] = vertex[1];
		if (Minimum[2] > vertex[2])
			Minimum[2] = vertex[2];
	}

	void AddVertex(double x, double y, double z)
	{
		AddVertex(Vector3d(x, y, z));
	}

	void AddNormal(const Vector3d& normal)
	{
		_normals.push_back(normal);
	}

	//void AddFace(const Face& face)
	//{
	//	_faces.push_back(face);
	//	_vertIndices.push_back(face.vertIndexes[0]);
	//	_vertIndices.push_back(face.vertIndexes[1]);
	//	_vertIndices.push_back(face.vertIndexes[2]);
	//}

	void AddTextureCoord(double u, double v)
	{
		_texCoords.push_back(Vector2d(u, v));
	}

	void AddFace(int v0, int v1, int v2, int t0, int t1, int t2, int n0, int n1, int n2)
	{
		_vertIndices.push_back(v0);
		_vertIndices.push_back(v1);
		_vertIndices.push_back(v2);
		_texCoordIndices.push_back(t0);
		_texCoordIndices.push_back(t1);
		_texCoordIndices.push_back(t2);
		_normIndices.push_back(n0);
		_normIndices.push_back(n1);
		_normIndices.push_back(n2);

		_faces.push_back(Face{3, 
			&_vertIndices[_vertIndices.size() - 3],
			&_normIndices[_normIndices.size() - 3],
			&_texCoordIndices[_texCoordIndices.size() - 3]
		});
	}

	void AddDirectedLight(const Vector3d& direction)
	{
		_directedLights.push_back(normalize(direction));
	}

	void SetTexture(Texture * texture)
	{
		_texture = texture;
	}

	const std::vector<Vector3d>& Vertices() const { return _vertices; }
	const std::vector<Vector3d>& Normals() const { return _normals; }
	const std::vector<Vector2d>& TextureCoords() const { return _texCoords; }
	const std::vector<Face>&	Faces() const { return _faces; }

	const std::vector<unsigned int>&	VertIndices() const { return _vertIndices; }
	const std::vector<unsigned int>&	NormIndices() const { return _normIndices; }
	const std::vector<unsigned int>&	TexCoordIndices() const { return _texCoordIndices; }

	bool Diffuse(double u, double v, Vector3d normal, RgbColor& color, Matrix4d4d& transform)
	{
		if (_directedLights.size() == 0) return false;
		auto light = normalize(Vector3d(transform * Vector4d(_directedLights[0], 1)));
		double dotP = dot(light, normal);
		if (dotP > 0) {
			color = _texture->GetColor(u, v);
			color[0] *= dotP;
			color[1] *= dotP;
			color[2] *= dotP;
			return true;
		}
		return false;
	}

	void GLDraw()
	{

	}

	Matrix4d4d ModelMatrix;

private:
	std::vector<Vector3d>	_vertices;
	std::vector<Vector3d>	_normals;
	std::vector<Vector2d>	_texCoords;
	std::vector<Face>		_faces;

	std::vector<unsigned int>	_vertIndices;
	std::vector<unsigned int>	_normIndices;
	std::vector<unsigned int>	_texCoordIndices;

	Texture * _texture;
	std::vector<Vector3d> _directedLights;

public:
	Vector3d Maximum;
	Vector3d Minimum = Vector3d(0, 0, 0);
};

#endif // _MODEL_H_