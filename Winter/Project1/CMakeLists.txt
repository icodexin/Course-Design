cmake_minimum_required(VERSION 3.17)

set(ProjectName "Porject1")

project(${ProjectName})

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src/includes")

AUX_SOURCE_DIRECTORY("${PROJECT_SOURCE_DIR}/src" DIR_SRCS)

add_executable(MazePath ${DIR_SRCS})