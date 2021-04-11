cmake_minimum_required(VERSION 3.19)
project(SortingAlgorithm)
set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics window audio network system REQUIRED)
add_executable(SFMLTest main.cpp)
target_link_libraries(SFMLTest sfml-graphics sfml-window sfml-audio sfml-network sfml-system)


