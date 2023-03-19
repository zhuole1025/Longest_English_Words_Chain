# CMakeList.txt: Longest_English_Words_Chain 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("Longest_English_Words_Chain")

# Check if OpenMP is supported by the compiler
# find_package(OpenMP REQUIRED)

# Add OpenMP flags to the compiler
# if(OPENMP_FOUND)
#     message("OPENMP FOUND")
#     set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#     set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
# else()
#     message(FATAL_ERROR "openmp not found!")
# endif()

# test
## enable_testing()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
# 将源代码添加到此项目的可执行文件。
add_library(core SHARED src/core.cpp src/core.h src/solver.h src/graph.h src/word.h )
add_executable (Wordlist   "src/main.cpp" "src/core.h" "src/core.cpp" "src/graph.h" "src/solver.h" "src/word.h" )

# add_test(NAME MyTest COMMAND TestAddition)
# target_link_libraries(Longest_English_Words_Chain OpenMP::OpenMP_CXX)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Wordlist PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
