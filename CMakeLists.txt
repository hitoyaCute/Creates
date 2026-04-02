cmake_minimum_required(VERSION 3.28)

project(Creates LANGUAGES CXX)                                  # set the project name and specify that it uses C++
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)  # set output directory for the executable
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)       # build static libraries by default

# export compile info
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# download and install the sfml lib
# include(FetchContent)
# FetchContent_Declare(SFML
#     GIT_REPOSITORY https://github.com/SFML/SFML.git   # specify the repository to clone from
#     GIT_TAG 3.0.1                                     # specify the version of sfml to download
#     GIT_SHALLOW ON                                    # shallow clone to speed up the download
#     EXCLUDE_FROM_ALL                                  # exclude from all to prevent sfml from being built as a separate target
#     SYSTEM                                            # treat sfml as a system library to avoid warnings
# )
# 
# FetchContent_MakeAvailable(SFML)

# Disable unused SFML components before adding the subdirectory
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_AUDIO   OFF CACHE BOOL "" FORCE)

add_subdirectory(./extern_lib/sfml-src SYSTEM)

# set optimizer flag for sfml libraries
set_target_properties(sfml-graphics sfml-window sfml-system 
                      PROPERTIES COMPILE_OPTIONS "-O3")

# template
# will be populated by the script to add all cpp files
add_executable(${PROJECT_NAME}
    ./src/ui/shapes/basicShape.cpp
    ./src/ui/Primitives/Button.cpp
    ./src/app/event.cpp
    ./src/app/main.cpp
    ./src/app/simulation/Objects.cpp
    ./src/app/simulation/test.cpp
    ./src/app/interface/scene/scenes.cpp
    ./lib/Interpolated/Interpolated.cpp)


# link sfml libs
set(SFML_LIBS SFML::Graphics SFML::Window SFML::System)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_LIBS})


# set debug symbols and optimization level with warnings and c++20 standard
target_compile_options(${PROJECT_NAME} PRIVATE -g -O1 -Wall -std=c++20)

# include headers sources
target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/lib")

# add environment variable for RES folder to be used in the code
target_compile_definitions(${PROJECT_NAME} PRIVATE
    RES_DIR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res/")

# copy assets to output directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD                # specify the target and when to execute the command
    COMMAND ${CMAKE_COMMAND} -E copy_directory       # copy command
    "${CMAKE_SOURCE_DIR}/res"                        # source directory
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res")         # destination directory

