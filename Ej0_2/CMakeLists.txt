 
cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "-static")

project(Ej0_2 LANGUAGES CXX)
add_executable(main main.cpp holaMundo.h holaMundo.cpp )
target_link_libraries(main pthread)

project(Ej0_2Cliente LANGUAGES CXX)
add_executable(mainClient main.cpp holaMundo_stub.h holaMundo_stub.cpp utils.h utils.cpp)
target_link_libraries(mainClient pthread)

project(Ej0_2Server LANGUAGES CXX)
add_executable(mainServer mainServer.cpp holaMundo_imp.h holaMundo_imp.cpp utils.h utils.cpp holaMundo.h holaMundo.cpp)
target_link_libraries(mainServer pthread)