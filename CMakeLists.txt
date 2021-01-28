cmake_minimum_required(VERSION 3.5)

project(k-core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set( CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} \
	-fopenmp \
	-march=native \
	-mavx \
	-Wall"
)
set( CMAKE_CXX_FLAGS_DEBUG
  "${CMAKE_CXX_FLAGS_DEBUG} \
	-fprofile-arcs -ftest-coverage \
	-g \
	-O0"
)
set( CMAKE_CXX_FLAGS_RELEASE
  "${CMAKE_CXX_FLAGS_RELEASE} \
  -Ofast"
)

set(
  basepath
    "${CMAKE_SOURCE_DIR}"
)

add_subdirectory(src)
