# CMakeList.txt: Longest_English_Words_Chain 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("Longest_English_Words_Chain")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
# 将源代码添加到此项目的可执行文件。
add_executable (Longest_English_Words_Chain   "src/main.cpp" "src/core.h" "src/core.cpp")

# add_subdirectory(src)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Longest_English_Words_Chain PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
