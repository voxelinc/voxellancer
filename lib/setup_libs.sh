#!/bin/sh

git clone https://github.com/nigels-com/glew.git glew
cd glew
git checkout 98e09c1564f799040218b97ad541d6d061ffbb00
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


