#!/bin/bash
sudo apt install libsdl2* libglew* libglut* libglew-dev:i386 libsndfile-dev -y
cmake . && cmake . 1>/dev/null # deux fois car sinon erreur de compilation
