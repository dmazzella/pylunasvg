cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(PYBIND11_FINDPYTHON ON)

project(pylunasvg)

add_subdirectory(pybind11)
add_subdirectory(lunasvg)
pybind11_add_module(pylunasvg src/pylunasvg.cpp)

target_link_libraries(pylunasvg PUBLIC pybind11::module)
target_link_libraries(pylunasvg PRIVATE lunasvg)
target_compile_definitions(pylunasvg PRIVATE)
target_compile_definitions(pylunasvg PRIVATE VERSION_INFO="${PYLUNASVG_VERSION_INFO}")