// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// mesh_formatter.h
//  header for tool that reads in wavefront obj, converts to vertices[] 
// -----------------------------------------------------------------------------

#ifndef MESH_FORMATTER_H
#define MESH_FORMATTER_H

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include <string>
#include <fstream>
#include <ctype.h>
#include <vector>

class MeshFormatter {
public:
	MeshFormatter() = default;
	~MeshFormatter() = default;

	std::string formatName(const char*);
	std::string formatMesh(const char*);
	std::string formatMeshIncludeGuards(const char*);

	std::string m_name;

private:
};

#endif // MESH_FORMATTER_H