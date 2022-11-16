#! /bin/zsh

cd external
git clone https://github.com/Microsoft/vcpkg.git
./vcpkg/bootstrap-vcpkg.sh -disableMetrics

cd ..
cmake -S . -B build