// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// mesh_formatter.hpp
//  header for tool that reads in wavefront obj, converts to vertices[] 
// -----------------------------------------------------------------------------

#ifndef MESH_FORMATTER_HPP
#define MESH_FORMATTER_HPP

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

	std::string formatMesh(const char*);
	std::string formatIncludeGuards(const char*);

private:

};

#endif // MESH_FORMATTER_HPP