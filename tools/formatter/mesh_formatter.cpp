// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// mesh_formatter.cpp
//  implementation for tool that reads in wavefront obj, converts to vertices[] 
// -----------------------------------------------------------------------------

#include "mesh_formatter.hpp"

// formatName(): ---------------------------------------------------------------
std::string MeshFormatter::formatName(const char* input) {
	std::string name = "";
	
	int i = 0;
	char ch;
	while (input[i] && input[i] != '.') {
		ch = input[i];
		if (i == 0) {
			name += toupper(ch);
		}
		else {
			name += ch;
		}
		i++;
	}

	return name;
}

// formatMesh(): ---------------------------------------------------------------
std::string MeshFormatter::formatMesh(const char* input) {
	std::string str = "";
	std::string header = "";

	FILE* objFile = fopen(input, "r");
	char line[1024];

	std::vector<glm::vec3> vertices;
	glm::vec3 v;

	std::vector<glm::vec2> texcoords;
	glm::vec2 tc;

	int vertexA, textureA, normalA, 
		vertexB, textureB, normalB, 
		vertexC, textureC, normalC;
	int faceCount = 0;

	while (fgets(line, 1024, objFile)) {
        // vertex information
		if (strncmp(line, "v ", 2) == 0) {
			// create an array of vertex information (x, y, z) and keep count
			sscanf(line, "v %f %f %f", &v[0], &v[1], &v[2]);
			vertices.emplace_back(v);
		}

		// texture coordinate information 
		if (strncmp(line, "vt ", 3) == 0) {
			// create an array of tex coord information (u, v) and keep count
			sscanf(line, "vt %f %f", &tc[0], &tc[1]);
			texcoords.emplace_back(tc);
		}

		// face information - use to populate the returnString
		if (strncmp(line, "f ", 2) == 0) {
			sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&vertexA, &textureA, &normalA,
            	&vertexB, &textureB, &normalB, 
            	&vertexC, &textureC, &normalC
            );

			// first vertex of face
			str += 	"\t\t";
			str += 	std::to_string(vertices[vertexA - 1][0]) + "f, " + 
					std::to_string(vertices[vertexA - 1][1]) + "f, " + 
					std::to_string(vertices[vertexA - 1][2]) + "f, ";
			str += 	"1.0f, 1.0f, 1.0f, ";
			str += 	std::to_string(texcoords[textureA - 1][0]) + "f, " + 
					std::to_string(texcoords[textureA - 1][1]) + "f, ";
			// newline for the next vertex
			str += 	"\n";

			// second vertex of face
			str += 	"\t\t";
			str += 	std::to_string(vertices[vertexB - 1][0]) + "f, " + 
					std::to_string(vertices[vertexB - 1][1]) + "f, " + 
					std::to_string(vertices[vertexB - 1][2]) + "f, ";
			str += 	"1.0f, 1.0f, 1.0f, ";
			str += 	std::to_string(texcoords[textureB - 1][0]) + "f, " + 
					std::to_string(texcoords[textureB - 1][1]) + "f, ";
			// newline for the next vertex
			str += 	"\n";

			// third vertex of face
			str += 	"\t\t";
			str += 	std::to_string(vertices[vertexC - 1][0]) + "f, " + 
					std::to_string(vertices[vertexC - 1][1]) + "f, " + 
					std::to_string(vertices[vertexC - 1][2]) + "f, ";
			str += 	"1.0f, 1.0f, 1.0f, ";
			str += 	std::to_string(texcoords[textureC - 1][0]) + "f, " + 
					std::to_string(texcoords[textureC - 1][1]) + "f, ";
			// newline for the next vertex
			str += 	"\n";

			faceCount++;
		}
	}

	// remove the very last comma from the array (first newline, then space, then comma)
	str.pop_back();
	str.pop_back();
	str.pop_back();

	// add closing } at end of m_vertices[]
	str = str + "\n\t};\n\n";

	// add m_verticesSize for populating VBO 
	float f;
	str = str + "\tint m_verticesSize = " + std::to_string(faceCount * 3 * 8 * sizeof(f)) + ";\n\n";

	// add m_vertexCount for RenderSystem to use
	str = str + "\tint m_vertexCount = " + std::to_string(faceCount * 3) + ";\n";

	// add closing } at end of struct MeshComponent
	str = str + "}; \n\n";

	// had to wait until after reading file to make header - needed faceCount
	header += "struct Mesh";
	header += m_name;
	header += "Component { \n";
	header += "\t" "float m_vertices[";
	header += std::to_string(faceCount * 3 * 8);
	header += "] = { \n";
	str = header + str;

	fclose(objFile);
	return str;
}

// formatMeshIncludeGuards(): --------------------------------------------------
std::string MeshFormatter::formatMeshIncludeGuards(const char* input) {
	std::string str;

	str += "COMPONENT_MESH_";
	
	int i = 0;
	char ch;

	while (input[i] && input[i] != '.') {
		ch = input[i];
		str += toupper(ch);
		i++;
	}

	str += "_HPP";

	return str;
}

// formatShape(): --------------------------------------------------------------
std::string MeshFormatter::formatShape(const char* input) {
	std::string str = "";

	return str;
}

// formatShapeIncludeGuards(): -------------------------------------------------
std::string MeshFormatter::formatShapeIncludeGuards(const char* input) {
	std::string str;

	str += "COMPONENT_SHAPE_";
	
	int i = 0;
	char ch;

	while (input[i] && input[i] != '.') {
		ch = input[i];
		str += toupper(ch);
		i++;
	}

	str += "_HPP";

	return str;
}