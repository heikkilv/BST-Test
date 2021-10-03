cmake_minimum_required(VERSION 3.12)

project(BST-Test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(fmt)

add_executable(
    ${PROJECT_NAME}
    "src/main.cpp"
)

target_link_libraries (BST-Test LINK_PUBLIC fmt)
target_include_directories (BST-Test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/fmt)
