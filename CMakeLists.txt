cmake_minimum_required(VERSION 3.26)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -Wpedantic -g)

project(NeuralNet)

# add files
include_directories(./include)
add_executable(NeuralNet
    src/main.cpp
    src/Net.cpp
)

# OpenGL Setup
#find_package(OpenGL REQUIRED)
#target_link_libraries(main OpenGL::GL)

# GLM Setup
#set(glm_DIR ./libs/glm/cmake/glm) # if necessary
#find_package(glm REQUIRED)
#find_package(glfw3 3.3  REQUIRED)
#target_link_libraries(main glm::glm)
#target_link_libraries(main glfw)
