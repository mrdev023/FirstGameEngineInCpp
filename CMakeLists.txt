#require opengl,glew,glut,glu,al,alc,sndfile library

cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0015 NEW)

#Configuration du projet
project(TestSDL2)
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})



#Inclusion de Boost

include_directories(/usr/include)

link_directories(/usr/lib)



#Configuration de l'exécutable

file(
        GLOB_RECURSE
        source_files
        src/*
)

add_executable(
        main
        ${source_files}
)



#Configuration de l'édition de liens

target_link_libraries(
        main
        openal
        alut
        sndfile
        SDL2main
        SDL2
        SDL2_image
        SDL2_ttf
        SDL2_mixer
        GLEW
        glut
        GL
        GLU
)