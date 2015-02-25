#ifndef _OBJ_PARSER_H_
#define _OBJ_PARSER_H_

#include "Model.h"
#include <string>
#include <istream>

class ObjParser
{
public:
	static Model * Parse(std::string filename);
	static Model * Parse(std::istream& inS);

private:
	static Model * currentModel;

	static void ParseLine(std::string line);
};

#endif // _OBJ_PARSER_H_