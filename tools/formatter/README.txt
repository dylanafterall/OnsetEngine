The binary, "MeshFormatter", accepts a Wavefront .obj file (triangulated mesh only),
and produces a .h header file correctly formatted for OpenGL VBO processing. 

The CMake project 'OnsetEngine' also creates MeshFormatter, in the build directory.
After using the build.sh script in the project's root directory, you can then use
the formatter.sh script to access the MeshFormatter. Follow the below instructions.

To use:
1) Add the input wavefront .obj file to assets/models
2) In terminal, navigate to OnsetEngine's root directory
3) In terminal, enter:  ./formatter.sh <input_file> <output_file>
        For example:    ./formatter.sh "cube.obj" "component_mesh_cube.h"
4) The output .h file has been generated and added to include/meshes
4) Add output .h file  to include/component_all.h