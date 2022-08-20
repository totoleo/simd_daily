cmake_minimum_required(VERSION 3.0.0)
project(simd VERSION 0.1.0)

# include(CTest)
# enable_testing()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(benchmark REQUIRED)

# add_compile_options("-mavx")
add_compile_options("-mavx2")
add_compile_options("-mfma")
add_compile_options("-std=c++2a")
add_compile_options(-funroll-loops)

add_executable(simd main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)

add_executable(bench strings.cpp bench.cpp)
target_link_libraries(bench PUBLIC Threads::Threads)
target_link_libraries(bench PRIVATE benchmark::benchmark)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
