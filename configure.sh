#! /bin/zsh

echo "DOWNLOADING LUA"
cd external/lua/lua
curl -R -O http://www.lua.org/ftp/lua-5.4.4.tar.gz
tar zxf lua-5.4.4.tar.gz
cd ..
cd ..
cd ..

echo "DOWNLOADING GIT SUBMODULES"
git submodule add https://github.com/g-truc/glm.git external/glm
git submodule add https://github.com/skypjack/entt.git external/entt
git submodule add https://github.com/erincatto/box2d.git external/box2d
git submodule add https://github.com/nothings/stb.git external/stb/stb
git submodule add https://github.com/ThePhD/sol2.git external/sol2
git submodule add https://github.com/gabime/spdlog.git external/spdlog
git submodule add https://github.com/google/googletest.git external/googletest

echo "CONFIGURING CMAKE"
cmake -S . -B build/
