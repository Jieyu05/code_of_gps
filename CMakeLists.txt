#cmake的版本号
cmake_minimum_required(VERSION 3.16)
#项目名称
project(test)
#编译器C++标准
set(CMAKE_CXX_STANDARD 14)
#生成目标文件和指定源代码文件
add_executable(test judge.h judge.cpp main.cpp)
