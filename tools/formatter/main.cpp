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
	formatter.m_name = formatter.formatName(argv[1]);
	std::string meshIncludeGuards = formatter.formatMeshIncludeGuards(argv[1]);
	std::string shapeIncludeGuards = formatter.formatShapeIncludeGuards(argv[1]);

	std::ofstream outputMeshFile (argv[2]);
	outputMeshFile << "// -----------------------------------------------------------------------------" << "\n";
	outputMeshFile << "// Onset Engine" << "\n";
	outputMeshFile << "// https://github.com/dylanafterall/OnsetEngine.git" << "\n";
	outputMeshFile << "//" << "\n";
	outputMeshFile << "// " << argv[2] << "\n";
	outputMeshFile << "//  component to hold vertex (x,y,z / r,g,b / u,v) data for OpenGL rendering " << "\n";
	outputMeshFile << "// -----------------------------------------------------------------------------" << "\n";
	outputMeshFile << "\n";
	outputMeshFile << "#ifndef " << meshIncludeGuards << "\n";
	outputMeshFile << "#define " << meshIncludeGuards << "\n";
	outputMeshFile << "\n";
	// pass in input (wavefront obj) file to be formatted for OpenGL rendering
	outputMeshFile << formatter.formatMesh(argv[1]);
	outputMeshFile << "#endif // " << meshIncludeGuards << std::endl;
	outputMeshFile.close();

	std::ofstream outputShapeFile (argv[3]);
	outputShapeFile << "// -----------------------------------------------------------------------------" << "\n";
	outputShapeFile << "// Onset Engine" << "\n";
	outputShapeFile << "// https://github.com/dylanafterall/OnsetEngine.git" << "\n";
	outputShapeFile << "//" << "\n";
	outputShapeFile << "// " << argv[3] << "\n";
	outputShapeFile << "//  component to hold vertex (x,y,z / r,g,b / u,v) data for Box2D physics " << "\n";
	outputShapeFile << "// -----------------------------------------------------------------------------" << "\n";
	outputShapeFile << "\n";
	outputShapeFile << "#ifndef " << shapeIncludeGuards << "\n";
	outputShapeFile << "#define " << shapeIncludeGuards << "\n";
	outputShapeFile << "\n";
	outputShapeFile << "#include \"box2d/box2d.h\"\n";
	// pass in input (wavefront obj) file to be formatted for Box2D physics
	outputShapeFile << formatter.formatShape(argv[1]);
	outputShapeFile << "#endif // " << shapeIncludeGuards << std::endl;
	outputShapeFile.close();

	return 0;
}