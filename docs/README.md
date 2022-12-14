# Onset Engine

<p>The Onset Engine is an ECS game engine written in C++, with 2D physics and 3D rendering. Shaders are written in GLSL. 
The engine uses the OpenGL API for rendering. <br>
I am building this engine for my own education. It is not intended for 
commerical application. Its development will be ongoing, as I try to incorporate 
new techniques and practices over time. 
</p>

<p>Features:
<ul>
    <li> </li>
    <li> </li>
    <li>Tool to convert wavefront .obj (triangulated mesh) files to array for OpenGL VBO/VAO processing </li>
    <li>External library management and versioning via vcpkg integration w/ CMake </li>
    <li>HTML and LaTeX documentation via Doxygen integration w/ CMake </li>
    <li>Rotating file logs (default 3 5MB files) via spdlog, log levels dependent on build type </li>
</ul>
</p>

## Infrastructure

<p>External Libraries:
<ul>
    <li><a href="https://github.com/Dav1dde/glad">Dav1dde/glad</a> </li>
    <li><a href="https://www.glfw.org/">GLFW</a> </li>
    <li><a href="https://www.opengl.org/sdk/libs/GLM/">GLM</a> </li>
    <li><a href="https://github.com/skypjack/entt">skypjack/entt</a> </li>
    <li><a href="https://box2d.org/">erincatto/box2d</a> </li>
    <li><a href="https://github.com/gabime/spdlog">gabime/spdlog</a> </li>
    <li><a href="https://github.com/ocornut/imgui">ocornut/imgui</a> </li>
    <li><a href="https://github.com/nothings/stb">nothings/stb</a> </li>
</ul>
</p>

<p>Tools:
<ul>
    <li>Editor: <a href="https://github.com/neovim/neovim">Neovim</a>, <a href="https://code.visualstudio.com/">VS Code</a> </li>
    <li>Build System: <a href="https://cmake.org/">CMake</a>, <a href="https://vcpkg.io/en/index.html">vcpkg</a> </li>
    <li>Documentation: <a href="https://www.doxygen.nl/">Doxygen</a> </li>
    <li>API: <a href="https://www.opengl.org/">OpenGL</a> </li>
    <li>LSP: <a href="https://clangd.llvm.org/">clangd</a> </li>
    <li>Static Analysis: <a href="http://cppcheck.net/">Cppcheck</a>, <a href="https://clang.llvm.org/extra/clang-tidy/">Clang-Tidy</a> </li>
    <li>Dynamic Analysis: <a href="https://lldb.llvm.org/">LLDB</a>, <a href="https://valgrind.org/">Valgrind</a>, <a href="https://github.com/aristocratos/btop">btop++</a>, <a href="https://github.com/wolfpld/tracy">Tracy Profiler</a> </li>
</ul>
</p>

## Installation

<p>These instructions are for my personal reference. Please adjust for your OS, Distro, Package Manager, etc.

<ol>
    <li>Get OpenGL libraries: </li>
        <ul>
            <li>if macOS: </li>
                <ul>
                    <li><a href="https://developer.apple.com/xcode/">download Xcode developer tools:</a> </li>
                    <li>xcode-select --install </li>
                </ul>
            <li>if Ubuntu: </li>
                <ul>
                    <li>sudo apt-get update </li>
                    <li>sudo apt-get install build-essential </li>
                    <li>sudo apt-get install libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev libxcursor-dev libxinerama-dev libxi-dev </li>
                </ul>
        </ul> 
    <li>Get CMake: </li>
        <ul>
            <li>if macOS: </li>
                <ul>
                    <li><a href="https://cmake.org/download/">download and install cmake-x.xx.x-macos-universal.dmg binary release</a> </li>
                    <li>Follow "Tools"->"How to Install For Command Line Use" </li>
                    <li>(Alternately): brew install cmake </li>
                </ul>
            <li>if Ubuntu: </li>
                <ul>
                    <li>sudo apt-get install cmake </li>
                </ul>
        </ul>
    <li>Get Doxygen: </li>
        <ul>
            <li>if macOS: </li>
                <ul>
                    <li>Follow instructions at: https://www.doxygen.nl/download.html </li>
                    <li>(Alternately): brew install doxygen </li>
                    <li>(Alternately): brew install graphviz </li>
                </ul>
            <li>if Ubuntu: </li>
                <ul>
                    <li>sudo apt-get install doxygen </li>
                    <li>sudo apt-get install graphviz </li>
                </ul>
        </ul>
    <li>In desired download location: </li>
        <ul>
            <li>git clone https://github.com/dylanafterall/OnsetEngine.git </li>
        </ul>
    <li>cd into OnsetEngine/ root directory, enter following commands: </li>
        <ul>
            <li>if macOS: </li>
                <ul>
                    <li>./configure.sh </li>
                    <li>./build.sh </li>
                    <li>./run.sh </li>
                </ul>
            <li>if Ubuntu: </li>
                <ul>
                    <li>bash ./configure.sh </li>
                    <li>bash ./build.sh </li>
                    <li>bash ./run.sh </li>
                </ul>
        </ul>
</ol>
</p>

## Acknowledgements

<p>This project was inspired by:<br>
<ul> 
    <li>The online reference <a href="https://learnopengl.com/">"LearnOpenGL"</a>, by Joey deVries </li>
    <li>The online resource <a href="https://freepbr.com/">"Free PBR"</a>, by Brian </li>
    <li>The online tutorial series <a href="https://pikuma.com/courses">"C++ 2D Game Engine Development"</a>, by Gustavo
    Pezzi </li>
    <li>The book <a href="https://gameprogrammingpatterns.com/">"Game Programming Patterns"</a>, by Robert Nystrom </li>
    <li>The online reference <a href="https://thebookofshaders.com/">"The Book of Shaders"</a>, by Patricio Gonzalez Vivo and Jen Lowe </li>
</ul>
</p>
