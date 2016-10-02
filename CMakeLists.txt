#require opengl,glew,glut,glu,al,alc,sndfile library

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0015 NEW)

#Configuration du projet
project(TestSDL2)
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})



#Inclusion de Boost

IF (WIN32)
        include_directories($ENV{MINGW_HOME}/usr/include)
        link_directories($ENV{MINGW_HOME}/usr/lib)
ELSE()
        include_directories(/usr/include)
        link_directories(/usr/lib)
ENDIF()



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


IF (WIN32)
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
                glew32
                glut
                opengl32
                glu32
        ) 
ELSE()
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
ENDIF()