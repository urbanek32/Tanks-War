cmake_minimum_required(VERSION 3.10.0)
project (Tanks-War)

file(GLOB_RECURSE TANKSWAR_CL_SRC ${PROJECT_SOURCE_DIR}/*.cpp)
list(FILTER TANKSWAR_CL_SRC EXCLUDE REGEX ${PROJECT_SOURCE_DIR}/Ekran[12].cpp)
list(FILTER TANKSWAR_CL_SRC EXCLUDE REGEX ${PROJECT_SOURCE_DIR}/ImageButton.cpp)

include_directories(${PROJECT_SOURCE_DIR}/Box2D/include)
include_directories(${PROJECT_SOURCE_DIR}/SFML-1.6/include)
#include_directories(${PROJECT_SOURCE_DIR}/SFML-1.6/lib/SFML-src/Audio)
include_directories(${PROJECT_SOURCE_DIR}/ENet/include)
include_directories(${PROJECT_SOURCE_DIR})

link_directories(${PROJECT_SOURCE_DIR}/SFML-1.6/lib)

add_executable(Tanks-War ${TANKSWAR_CL_SRC})
target_link_libraries(Tanks-War -lsfml-window -lsfml-graphics -lsfml-system -lsfml-network)
