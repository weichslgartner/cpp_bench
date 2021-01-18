cmake_minimum_required(VERSION 3.19)

# set the project name
project(str_bench)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Threads REQUIRED) 
find_package(folly REQUIRED) 


add_executable(strcat_bench strcat_bench.cc)
target_link_libraries(strcat_bench PRIVATE ${CONAN_LIBS}  folly double-conversion glog)


