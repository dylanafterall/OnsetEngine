# Onset Engine

<p>The Onset Engine is a 2D, ECS (Entity-Component-System) game engine written in C++. Shaders are written in GLSL and scripts are written in Lua. It uses the OpenGL API for rendering. <br>
I am building this engine for my own education. It is not intended for 
commerical application. Its development will be ongoing, as I try to incorporate 
new techniques and practices over time. 
</p>

<p>Features:
<ul>
    <li> </li>
    <li> </li>
    <li> </li>
</ul>
</p>

## Infrastructure

<p>Dependencies:
<ul>
    <li><a href="https://www.opengl.org/">OpenGL</a> </li>
    <li><a href="https://cmake.org/">CMake</a> </li>
</ul>
</p>

<p>External Libraries:
<ul>
    <li><a href="https://www.glfw.org/">GLFW</a> </li>
    <li><a href="https://www.opengl.org/sdk/libs/GLM/">GLM</a> </li>
    <li><a href="https://www.lua.org/">Lua v.5.4.4</a> </li>
    <li><a href="https://github.com/Dav1dde/glad">Dav1dde/glad</a> </li>
    <li><a href="https://box2d.org/">erincatto/box2d</a> </li>
    <li><a href="https://github.com/skypjack/entt">skypjack/entt</a> </li>
    <li><a href="https://github.com/nothings/stb">nothings/stb</a> </li>
    <li><a href="https://github.com/ocornut/imgui">ocornut/imgui</a> </li>
    <li><a href="https://github.com/ThePhD/sol2">ThePhD/sol2</a> </li>
    <li><a href="https://github.com/gabime/spdlog">gabime/spdlog</a> </li>
    <li><a href="https://github.com/google/googletest">google/googletest</a> </li>
</ul>
</p>

<p>Tools:
<ul>
    <li>OS: Ubuntu / macOS </li>
    <li>Editor: Neovim </li>
    <li>Build System: CMake </li>
    <li>LSP: clangd </li>
    <li>Static Analysis: Cppcheck, Clang-Tidy </li>
    <li>Dynamic Analysis: LLDB, Valgrind (Memcheck, Cachegrind) </li>
    <li>Testing: CTest, GoogleTest </li>
    <li>Documentation: Doxygen </li>
</ul>
</p>

## Installation

<p>These instructions are for my personal reference. Please adjust for your OS, Distro, Package Manager, etc.

<ol>
    <li> Get OpenGL libraries: </li>
        <ul>
            <li>if macOS: </li>
                <ul>
                    <li><a href="https://developer.apple.com/xcode/">download Xcode developer tools</a> </li>
                    <li>xcode-select --install </li>
                </ul>
            <li>if Ubuntu: </li>
                <ul>
                    <li>sudo apt-get update </li>
                    <li>sudo apt-get install build-essential </li>
                    <li>sudo apt-get install libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev libxcursor-dev libxinerama-dev libxi-dev </li>
                </ul>
        </ul> 
    <li> Get CMake: </li>
        <ul>
            <li>if macOS: </li>
                <ul>
                    <li><a href="https://cmake.org/download/">download and install cmake-x.xx.x-macos-universal.dmg binary release</a> </li>
                    <li>PATH="/Applications/CMake.app/Contents/bin":"$PATH" </li>
            </ul>
            <li>if Ubuntu: </li>
                <ul>
                    <li>sudo apt-get install cmake </li>
                    <li>if cmake --version (from apt-get install) is not recent enough: </li>
                        <ul>
                            <li>sudo apt-get install libssl-dev </li>
                            <li><a href="https://cmake.org/download/">download and extract cmake-x.xx.x.tar.gz release </a> </li>
                            <li>cd $CMAKE_DOWNLOAD_PATH </li>
                            <li>./configure </li>
                            <li>gmake </li>
                            <li>sudo make install </li>
                            <li>restart terminal </li>
                        </ul>
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
                    <li>sudo apt-get install curl </li>
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
    <li>The online tutorial series <a href="https://pikuma.com/courses">"C++ 2D Game Engine Development"</a>, by Gustavo
    Pezzi </li>
    <li>The book <a href="https://gameprogrammingpatterns.com/">"Game Programming Patterns"</a>, by Robert Nystrom </li>
    <li>The online reference <a href="https://learnopengl.com/">"LearnOpenGL"</a>, by Joey deVries </li>
    <li>The online reference <a href="https://thebookofshaders.com/">"The Book of Shaders"</a>, by Patricio Gonzalez Vivo and Jen Lowe </li>
</ul>
</p>
