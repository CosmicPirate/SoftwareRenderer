#include "ObjParser.h"
#include <sstream>


Model * ObjParser::currentModel = NULL;

Model * ObjParser::Parse(std::string filename)
{
	std::ifstream inS;
	inS.open(filename, std::ios::in);

	Model * model = Parse(inS);

	inS.close();

	return model;
}

Model * ObjParser::Parse(std::istream& inS)
{
	currentModel = new Model();

	std::string l;
	while (std::getline(inS, l))
	{
		ParseLine(l);
	}

	return currentModel;
}

void ObjParser::ParseLine(std::string line)
{
	std::string type;
	std::istringstream iss(line);

	if (!iss.eof())
		iss >> type;

	if (type == "v")
	{
		double v0, v1, v2;
		iss >> v0; iss >> v1; iss >> v2;
		currentModel->AddVertex(Vector3d(v0, -v1, v2));
	}
	else if (type == "vn")
	{
		double vn0, vn1, vn2;
		iss >> vn0 >> vn1 >> vn2;
		currentModel->AddNormal(Vector3d(vn0, vn1, vn2));
	}
	else if (type == "f")
	{
		char slash;
		//int v0, v1, v2, vt0, vt1, vt2, vn0, vn1, vn2;
		int v[3], vt[3], vn[3];
		bool hasTCoords = currentModel->TextureCoords().size() > 0;
		bool hasNormals = currentModel->Normals().size() > 0;

		for (int i = 0; i < 3; ++i) {
			iss >> v[i];
			if (hasTCoords)
				iss >> slash >> vt[i];
			if (hasNormals)
				iss >> slash >> vn[i];
		}

		currentModel->AddFace(
			v[0] - 1, v[1] - 1, v[2] - 1,
			vt[0] - 1, vt[1] - 1, vt[2] - 1,
			vn[0] - 1, vn[1] - 1, vn[2] - 1);
		//iss >> v0 >> slash >> vt0 >> slash >> vn0;
		//iss >> v1 >> slash >> vt1 >> slash >> vn1;
		//iss >> v2 >> slash >> vt2 >> slash >> vn2;
		//currentModel->AddFace(v0 - 1, v1 - 1, v2 - 1, vt0 - 1, vt1 - 1, vt2 - 1);
	}
	else if (type == "vt")
	{
		double u, v, z;
		iss >> u >> v >> z;
		currentModel->AddTextureCoord(u, v);
	}
}
