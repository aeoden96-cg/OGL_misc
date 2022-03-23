cmake_minimum_required(VERSION 3.16)

add_subdirectory(other_resources/learnopengl)

add_library(SHADER
        Shader.h
        Shader.cpp)
set_target_properties(SHADER    PROPERTIES PUBLIC_HEADER Shader.h)
target_include_directories (SHADER PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(RENDERER
        Renderer.cpp
        Renderer.hpp
        )
set_target_properties(RENDERER PROPERTIES PUBLIC_HEADER Renderer.hpp)
target_include_directories (RENDERER PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


find_package(Freetype REQUIRED)


add_library(TEXT_RENDERER

        TextRenderer.cpp
        TextRenderer.hpp
        )
target_link_libraries(TEXT_RENDERER
        ${FREETYPE_LIBRARIES})
set_target_properties(TEXT_RENDERER PROPERTIES PUBLIC_HEADER TextRenderer.hpp)
target_include_directories (TEXT_RENDERER PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${FREETYPE_INCLUDE_DIRS})



