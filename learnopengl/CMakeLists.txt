cmake_minimum_required(VERSION 3.16)

add_library(CAMERA
        Camera.hpp
        Camera.cpp)
set_target_properties(CAMERA    PROPERTIES PUBLIC_HEADER Camera.hpp)
target_include_directories (CAMERA PUBLIC ../../learnopengl)

add_library(MESH
        Mesh.cpp
        Mesh.hpp
        )
set_target_properties(MESH PROPERTIES PUBLIC_HEADER Mesh.hpp)
target_include_directories (MESH PUBLIC ../../learnopengl)

add_library(MODEL
        Model.cpp
        Model.hpp
        )
set_target_properties(MODEL PROPERTIES PUBLIC_HEADER Model.hpp)
target_include_directories (MODEL PUBLIC ../../learnopengl)
