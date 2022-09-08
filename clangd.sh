#! /bin/zsh

# generate compile_commands.json with -I flags for clangd
# deletes extra files added to root directory
# also deletes contents of build directory

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1

rm -rf bin
rm cmake_install.cmake
rm CMakeCache.txt
rm -rf CMakeFiles
rm  -rf lib
rm Makefile
rm -rf build/{*,.[^.]*}