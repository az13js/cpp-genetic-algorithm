# 替换此文件中的 GeneticAlgorithm.out 可以改变生成的可执行文件名
cmake_minimum_required(VERSION 3.10)
# 设置项目名称和项目版本
project(GeneticAlgorithm VERSION 0.1)
# 开启静态编译，静态编译会把程序运行时的链接库也一起编译到可执行文件里面
set(CMAKE_EXE_LINKER_FLAGS "-static")
# 设置编译器支持的C++语言版本的检查
set(CMAKE_CXX_STANDARD_REQUIRED True)
# 设置编译器C++语言版本
set(CMAKE_CXX_STANDARD 17)
# 生成记录项目版本的头文件
configure_file(GeneticAlgorithm.h.in GeneticAlgorithm.h)
# 设置为扫描当前目录及子目录下所有.cpp结尾的文件并添加到CPP_FILES
file(GLOB_RECURSE CPP_FILES ./ *.cpp)
# 设置为所有CPP_FILES中的文件都编译到可执行文件GeneticAlgorithm.out
add_executable(GeneticAlgorithm.out ${CPP_FILES})
# 给编译过程添加include的目录，这里是用于包含生成的记录项目版本的头文件
target_include_directories(GeneticAlgorithm.out PUBLIC "${PROJECT_BINARY_DIR}")
# 为C++程序提供多线程库的链接支持，不需要使用多线程来开发时可以注释掉下面三行
#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)
#target_link_libraries(GeneticAlgorithm.out PUBLIC Threads::Threads)
