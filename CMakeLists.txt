cmake_minimum_required(VERSION 3.14)
project(OpenMPTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(OpenMPTest main.cpp)

find_package(OpenMP REQUIRED) # Find the package
target_link_libraries(${PROJECT_NAME} ${OpenMP_CXX_LIBRARIES}) # Link against it for C++