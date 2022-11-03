The binary, "formatter", accepts a Wavefront .obj file (triangulated mesh only),
and produces a .hpp header file correctly formatted for OpenGL VBO processing. 

To use:
1) In terminal, navigate to tools/formatter/ directory
2) In terminal, enter "make" to build the formatter binary
3) Move copy of input wavefront .obj file to tools/formatter/
4) In terminal, enter "./formatter <input_file> <output_file>"
        For example: "./formatter "cube.obj" "component_mesh_cube.hpp""
5) Move input .obj file to desired location within engine (assets directory)
6) Move output .hpp file to desired location within engine (include directory)
7) Add <output_file> to "component_all.hpp"