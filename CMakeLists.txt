cmake_minimum_required(VERSION 3.20.0)
project(SMM_API)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

add_subdirectory("${CMAKE_SOURCE_DIR}/lib")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/")
