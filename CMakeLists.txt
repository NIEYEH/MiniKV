cmake_minimum_required(VERSION 3.16)

project(MiniKV)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)


file(
    GLOB_RECURSE
    SRC_FILES
    CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)


add_library(
    minikv_core
    ${SRC_FILES}
)


target_include_directories(
    minikv_core
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)


target_link_libraries(
    minikv_core
    PUBLIC
    Threads::Threads
)


add_executable(
    minikv-server
    app/server_main.cpp
)


target_link_libraries(
    minikv-server
    PRIVATE
    minikv_core
)


add_executable(
    minikv-cli
    app/client_main.cpp
)


target_link_libraries(
    minikv-cli
    PRIVATE
    minikv_core
)