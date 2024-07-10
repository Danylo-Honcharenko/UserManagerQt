cmake_minimum_required(VERSION 3.16)

project("UserManagerQt" VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(Qt6_DIR "D:\\lib\\qt6.7.1\\lib\\cmake\\Qt6")
set(Qt6GuiTools_DIR "D:\\lib\\qt6.7.1\\lib\\cmake\\Qt6GuiTools")
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_subdirectory("UserManagerQt")
