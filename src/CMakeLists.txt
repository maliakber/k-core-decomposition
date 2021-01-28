add_executable(k-core main.cpp)
add_executable(k-core-test unit-test.cpp)

target_link_libraries(
  k-core
    kcore
    common
)

target_link_libraries(
  k-core-test
    kcore
    common
)

add_subdirectory(common)
add_subdirectory(kcore)
