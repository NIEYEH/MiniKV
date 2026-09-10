cmake_minimum_required(VERSION 3.10)


project(MiniKV)


# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 头文件目录
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)


# 收集src目录下所有cpp文件
file(GLOB SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)


# 创建可执行文件
add_executable(
    minikv
    app/main.cpp
    ${SRC_FILES}
)

find_package(Threads REQUIRED)


target_link_libraries(
    minikv
    Threads::Threads
)