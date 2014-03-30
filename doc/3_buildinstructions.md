Build instructions
==================

git and cmake should be on the path!

**windows:**

Visual Studio 2013 is required

execute:

    git clone https://github.com/voxelinc/voxellancer.git
    pushd voxellancer
    git submodule init
    git submodule update
    pushd lib
    unzip lib.zip
    popd
    mkdir build
    pushd build
    cmake -G "Visual Studio 12 Win64" ..
    popd

now start voxellancer.sln und set the debugging working directory for voxellancer to "$(ProjectDir)/../.."

**linux:**

(tested on ubuntu 13.10)

execute:

    git clone https://github.com/voxelinc/voxellancer.git
    cd voxellancer
    ./lib/setup_libs.sh
    mkdir build
    cd build
    cmake ..
    make voxellancer
