#! /bin/zsh

echo "Downloading and extracting Lua 5.4.4 to external/lua/lua"
cd external/lua/lua
curl -R -O http://www.lua.org/ftp/lua-5.4.4.tar.gz
tar zxf lua-5.4.4.tar.gz
cd ..
cd ..
cd ..
cmake -S . -B build/
