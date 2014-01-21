#!/bin/bash

pushd `dirname $0`

# glew
git clone -b glew-1.10.0 git://git.code.sf.net/p/glew/code glew
pushd glew
make extensions
make -j8
popd

# glm
git clone -b 0.9.4.6 https://github.com/g-truc/glm.git glm

# glfw
git clone -b 3.0.3 https://github.com/glfw/glfw.git glfw
pushd glfw
git 
cmake . 
make -j8
popd

# bandit
git clone -b v1.1.4 https://github.com/joakimkarlsson/bandit.git bandit

# OculusSDK
unzip ovr_sdk_linux_0.2.5c.tar.zip

# glow
pushd ..
git submodule init
git submodule update
popd

# sfml - requires libopenal-dev libsndfile1-dev libjpeg-dev
git clone -b 2.1 https://github.com/LaurentGomila/SFML.git SFML-2.1
pushd SFML-2.1
cmake .
make sfml-audio
popd

popd
