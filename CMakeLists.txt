cmake_minimum_required(VERSION 3.28)
project(Lumera LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(lumera 
    src/main.cpp
    src/World.cpp
    src/SpatialGrid.cpp
    src/Lumie.cpp
)

target_include_directories(lumera PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)

target_compile_features(lumera PRIVATE cxx_std_17)
target_link_libraries(lumera PRIVATE SFML::Graphics)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
