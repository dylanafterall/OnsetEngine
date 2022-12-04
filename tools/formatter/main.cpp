// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// main.cpp
//  entry point for the mesh formatter tool 
// -----------------------------------------------------------------------------

#include "mesh_formatter.h"

int main(int argc, char* argv[]) {
	MeshFormatter formatter;
	formatter.m_name = formatter.formatName(argv[1]);
	std::string meshIncludeGuards = formatter.formatMeshIncludeGuards(argv[1]);

	std::ofstream outputMeshFile (argv[2]);
	outputMeshFile << "// -----------------------------------------------------------------------------" << "\n";
	outputMeshFile << "// Onset Engine" << "\n";
	outputMeshFile << "// https://github.com/dylanafterall/OnsetEngine.git" << "\n";
	outputMeshFile << "//" << "\n";
	outputMeshFile << "// " << argv[2] << "\n";
	outputMeshFile << "//  component to hold vertex (x,y,z / i,j,k / u,v) data for OpenGL rendering " << "\n";
	outputMeshFile << "// -----------------------------------------------------------------------------" << "\n";
	outputMeshFile << "\n";
	outputMeshFile << "#ifndef " << meshIncludeGuards << "\n";
	outputMeshFile << "#define " << meshIncludeGuards << "\n";
	outputMeshFile << "\n";
	// pass in input (wavefront obj) file to be formatted for OpenGL rendering
	outputMeshFile << formatter.formatMesh(argv[1]);
	outputMeshFile << "#endif // " << meshIncludeGuards << std::endl;
	outputMeshFile.close();

	return 0;
}