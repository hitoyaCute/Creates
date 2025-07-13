cmake_minimum_required(VERSION 3.28)
# set name
project(Creates LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
# set version 
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# downlaold and install the sfml lib
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME}
  ./src/main.cpp
  ./src/UIProcessor/ShapeDrawer/basicShape.cpp
  ./src/UIProcessor/Events/EventProcessor.cpp)


target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")


set(SFML_LIBS sfml-graphics sfml-window sfml-system)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)








