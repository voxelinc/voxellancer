#!/bin/sh

git clone -b glew-1.10.0 git://git.code.sf.net/p/glew/code glew
cd glew
make extensions
make -j8
cd ..

git clone -b 0.9.4.6 https://github.com/g-truc/glm.git glm

git clone -b 3.0.3 https://github.com/glfw/glfw.git glfw
cd glfw
git 
cmake . 
make -j8
cd ..

git clone -b v1.1.4 https://github.com/joakimkarlsson/bandit.git bandit

cd .. 
git submodule init
git submodule update


