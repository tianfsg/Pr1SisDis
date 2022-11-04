cmake_minimum_required (VERSION 3.5)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (multMatrix LANGUAGES CXX)
add_executable (multMatrix main_multMatrix.cpp multmatrix.cpp multmatrix.h)

project (multMatrixClient LANGUAGES CXX)
add_executable(mainClient main_multMatrix.cpp MultMatrix_cliente.h MultMatrix_cliente.cpp utils.h utils.cpp)
target_link_libraries(mainClient pthread)

project (multMatrixServer LANGUAGES CXX)
add_executable(mainServer mainServer.cpp MultMatrix_server.h MultMatrix_server.cpp utils.h utils.cpp multmatrix.h multmatrix.cpp)
target_link_libraries(mainServer pthread)