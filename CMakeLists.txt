cmake_minimum_required(VERSION 3.28)
project(LogicSim LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
set(SFML_LIBS sfml-graphics sfml-window sfml-system)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)
