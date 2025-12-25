cmake_minimum_required(VERSION 3.10)
project(Bookstore-2025)

# 设置 C++ 标准 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
# 包含头文件目录
# 这会让编译器在 include/ 文件夹下寻找 .h 文件
include_directories(${CMAKE_SOURCE_DIR}/include)

# 设置源文件列表
set(SOURCES
    src/main.cpp
    src/account_manager.cpp
    src/book_manager.cpp
    src/log_manager.cpp
    src/Paser.cpp
    src/utils.cpp
)
add_executable(code ${SOURCES} ${HEADERS})