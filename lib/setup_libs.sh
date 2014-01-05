#!/bin/sh

git clone https://github.com/nigels-com/glew.git glew
cd glew
make extensions
make -j8
cd ..

git clone https://github.com/g-truc/glm.git glm
cd glm
git fetch origin
git checkout 0.9.4
cd ..

git clone https://github.com/glfw/glfw.git glfw
cd glfw
cmake . 
make -j8
cd ..

cd ..
git clone https://github.com/joakimkarlsson/bandit.git bandit

cd .. 
git submodule init
git submodule update


