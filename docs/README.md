# Onset Engine

<p>The Onset Engine is an ECS game engine written in C++, with 2D physics and 3D rendering. Shaders are written in GLSL. 
The engine uses the OpenGL 3.3 Graphics API for rendering. <br>
I am building this engine for my own education. It is not intended for 
commerical application. Its development will be ongoing, as I try to incorporate 
new techniques and practices over time. 
</p>

<p>Features:
<ul>
    <li>Rendering: </li>
        <ul>
            <li>Lighting: </li>
            <ul>
                <li>Blinn-Phong Lighting Model </li>
                <li>Directional lights, point lights, spot lights </li>
                <li>Shadow Mapping: mono/omni directional mapping, percentage-closer filtering </li>
                <li>HDR ***(work in progress) </li>
                <li>Bloom ***(work in progress) </li>
            </ul>
            <li>PBR Textures: </li>
                <ul>
                    <li>Albedo </li>
                    <li>Metallic </li>
                    <li>Normal ***(work in progress)</li>
                </ul>
            <li>Blending (transparent sprites) </li>
            <li>Object outlining/highlighting (stenciling) </li>
            <li>Skybox (via GL_TEXTURE_CUBE_MAP) </li>
            <li>Face Culling (via GL_CULL_FACE) </li>
            <li>Multisample Anti-Aliasing (via GL_MULTISAMPLE) </li>
            <li>Gamma Correction (via GL_FRAMEBUFFER_SRGB) </li>
            <li>Model Instancing (via glDrawArraysInstanced) ***(work in progress) </li>
            <li>Text Rendering </li>
        </ul>
    <li>Audio effects ***(work in progress) </li>
    <li>Event System (utilizing Observer programming pattern) with adjustable Event Queue </li>
    <li>Ability to rebind keymaps during runtime (utilizing Command programming pattern) </li>
    <li>Developer Tools: </li>
    <ul>    
        <li>Tool to convert wavefront .obj (triangulated mesh) files to array for OpenGL VBO/VAO processing </li>
        <li>External library management and versioning via vcpkg integration w/ CMake </li>
        <li>HTML and LaTeX documentation via Doxygen integration w/ CMake </li>
        <li>Rotating file logs (default 3 5MB files) via spdlog, log levels dependent on build type </li>
    </ul>
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
    <li><a href="https://freetype.org/">FreeType</a> </li>
    <li><a href="https://github.com/kcat/openal-soft">kcat/openal-soft</a> </li>
    <li><a href="https://github.com/libsndfile/libsndfile">libsndfile/libsndfile</a> </li>
</ul>
</p>

<p>Tools:
<ul>
    <li>Editor: <a href="https://code.visualstudio.com/">VS Code</a>, <a href="https://github.com/neovim/neovim">Neovim</a> </li>
    <li>Build System: <a href="https://cmake.org/">CMake</a>, <a href="https://vcpkg.io/en/index.html">vcpkg</a> </li>
    <li>Documentation: <a href="https://www.doxygen.nl/">Doxygen</a> </li>
    <li>API: <a href="https://www.opengl.org/">OpenGL</a> </li>
    <li>LSP: <a href="https://clangd.llvm.org/">clangd</a> </li>
    <li>Static Analysis: <a href="http://cppcheck.net/">Cppcheck</a>, <a href="https://clang.llvm.org/extra/clang-tidy/">Clang-Tidy</a> </li>
    <li>Dynamic Analysis: <a href="https://lldb.llvm.org/">LLDB</a>, <a href="https://valgrind.org/">Valgrind</a>, <a href="https://github.com/aristocratos/btop">btop++</a>, <a href="https://github.com/wolfpld/tracy">Tracy Profiler</a>, <a href="https://renderdoc.org/">RenderDoc</a> </li>
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

<p>This project uses the following assets:<br>
<ul>
    Fonts:
    <ul>
        <li>The Nerd Font: <a href="https://www.nerdfonts.com/font-downloads">"MesloLG"</a>, from <a href="https://nerdfonts.com/">"nerdfonts.com"</a> </li>
    </ul>
    Textures:
    <ul>
        <li>The PBR material: <a href="https://freepbr.com/materials/angled-blocks-vegetation/">"Angled Blocks Vegetation"</a>, by Brian on <a href="https://freepbr.com/">"freepbr.com"</a> </li>
        <li>The PBR material: <a href="https://freepbr.com/materials/black-white-tile-pbr/">"Black White Tile"</a>, by Brian on <a href="https://freepbr.com/">"freepbr.com"</a> </li>
        <li>The PBR material: <a href="https://freepbr.com/materials/dull-metal/">"Dull Metal"</a>, by Brian on <a href="https://freepbr.com/">"freepbr.com"</a> </li>
        <li>The PBR material: <a href="https://freepbr.com/materials/light-gold-pbr-metal-material/">"Light Gold"</a>, by Brian on <a href="https://freepbr.com/">"freepbr.com"</a> </li>
        <li>The PBR material: <a href="https://freepbr.com/materials/rusted-steel/">"Rusted Steel"</a>, by Brian on <a href="https://freepbr.com/">"freepbr.com"</a> </li>
    </ul>
    Audio:
    <ul>
        <li>Sound Effects: <a href="https://opengameart.org/content/ui-sounds">"UI Sounds"</a>, by StumpyStrust on <a href="https://opengameart.org/">"opengameart.org"</a> </li>
    </ul>
</ul>
</p>

<p>This project was inspired by:<br>
<ul> 
    <li>The online reference <a href="https://learnopengl.com/">"LearnOpenGL"</a>, by Joey deVries </li>
    <li>The online tutorial series <a href="https://pikuma.com/courses">"C++ 2D Game Engine Development"</a>, by Gustavo
    Pezzi </li>
    <li>The book <a href="https://gameprogrammingpatterns.com/">"Game Programming Patterns"</a>, by Robert Nystrom </li>
    <li>The online reference <a href="https://thebookofshaders.com/">"The Book of Shaders"</a>, by Patricio Gonzalez Vivo and Jen Lowe </li>
    <li>The YouTube channel <a href="https://www.youtube.com/@CodeTechandTutorials/videos">"Code, Tech, and Tutorials"</a>, by Matthew Jay Early </li>
    <li>The online reference <a href="https://indiegamedev.net/2020/02/15/the-complete-guide-to-openal-with-c-part-1-playing-a-sound/">"The Complete Guide to OpenAL with C++"</a>, by Deckhead
</ul>
</p>