#!/bin/bash
if [ "$(uname)" == "Darwin" ]; then
    brew install glew
    brew install alut
    brew install sdl2_image
    brew install sdl2_ttf
    brew install sdl2_mixer
    brew install openal-soft
    brew install libsndfile
    brew install freeglut
    cmake . && cmake . 1>/dev/null # deux fois car sinon erreur de compilation       
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    sudo apt install libsdl2* libglew* libglut* libglew-dev:i386 libsndfile-dev -y
    cmake . && cmake . 1>/dev/null # deux fois car sinon erreur de compilation
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]; then
    # Do something under 32 bits Windows NT platform
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ]; then
    # Do something under 64 bits Windows NT platform
fi
