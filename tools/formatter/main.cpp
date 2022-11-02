// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// main.cpp
//  entry point for the mesh formatter tool 
// -----------------------------------------------------------------------------

#include "mesh_formatter.hpp"

int main(int argc, char* argv[]) {
	MeshFormatter formatter;
	std::string includeGuards = formatter.formatIncludeGuards(argv[1]);

	std::ofstream outputFile (argv[2]);

	outputFile << "// -----------------------------------------------------------------------------" << "\n";
	outputFile << "// Onset Engine" << "\n";
	outputFile << "// https://github.com/dylanafterall/OnsetEngine.git" << "\n";
	outputFile << "//" << "\n";
	outputFile << "// " << argv[2] << "\n";
	outputFile << "//  component to hold vertex (x,y,z / r,g,b / u,v) data for OpenGL rendering " << "\n";
	outputFile << "// -----------------------------------------------------------------------------" << "\n";
	outputFile << "\n";
	outputFile << "#ifndef " << includeGuards << "\n";
	outputFile << "#define " << includeGuards << "\n";
	outputFile << "\n";

	// pass in input (wavefront obj) file to be formatted for OpenGL 
	outputFile << formatter.formatMesh(argv[1]);

	outputFile << "#endif // " << includeGuards << std::endl;

	outputFile.close();
	return 0;
}