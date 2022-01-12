cmake_minimum_required(VERSION 3.16)

add_library(CAMERA
        Camera.hpp
        Camera.cpp)
set_target_properties(CAMERA    PROPERTIES PUBLIC_HEADER Camera.hpp)
target_include_directories (CAMERA PUBLIC ../../learnopengl)

add_library(MESH
        assimp/Mesh.cpp
        assimp/Mesh.hpp
        )
set_target_properties(MESH PROPERTIES PUBLIC_HEADER assimp/Mesh.hpp)
target_include_directories (MESH PUBLIC ../../learnopengl)

add_library(MODEL
        assimp/Model.cpp
        assimp/Model.hpp
        )
set_target_properties(MODEL PROPERTIES PUBLIC_HEADER assimp/Model.hpp)
target_include_directories (MODEL PUBLIC ../../learnopengl)
