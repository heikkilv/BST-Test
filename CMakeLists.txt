cmake_minimum_required(VERSION 3.1)

project(BST-Test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
    ${PROJECT_NAME}
    "src/bstnode.tpp"
    "src/main.cpp"
)
