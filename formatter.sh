#! /bin/zsh

cd assets/models
mv $1 ../../build

cd ..
cd ..
cd build
./MeshFormatter $1 $2

mv $1 ../assets/models
mv $2 ../include/meshes