#表明cmake的最小版本号
cmake_minimum_required(VERSION 3.20)

# 相当于定义了变量 PROJECT_NAME = "BuriedPoint"
set(PROJECT_NAME "BuriedPoint")

# cmake项目根目录的CMakeLists.txt都需要这个
project(${PROJECT_NAME} VERSION 1.1.1.1)

# 定义开关，表示是否编译动态库
option(BUILD_BURIED_SHARED_LIBS "build shared library" ON)

# 定义开关，表示是否编译静态库
option(BUILD_BURIED_STATIC_LIBS "build static library" ON)

# 定义开关，表示是否编译示例代码
option(BUILD_BURIED_EXAMPLES "build examples" OFF)

# 定义开关，表示是否编译单元测试程序
option(BUILD_BURIED_TEST "build unittest" OFF)

# ?
option(BUILD_BURIED_FOR_MT "build for /MT" OFF)

# MSVC 编译专用的配置，表示启动多线程编译，如果在Linux在，需要注释掉
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}/MP")

# ??
if(BUILD_BURIED_FOR_MT)
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
endif()

# 相当于libs = libs + winmm + iphlpapi + ws2_32 + dbghelp
set(LIBS ${LIBS} winmm iphlpapi ws2_32 dbghelp Kernel32)

# generate pdb file
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}/Zi")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}/Zi")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")

set(INCDIRS . lib ${CMAKE_BINARY_DIR})
include_directories(${INCDIRS})

# 表示启用C++20标准和C11标准
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}/std:c++20")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}/std:c11")

# 打印信息
message(STATUS "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}")

# Debug模式下定义DEBUG宏，Release模式下定义NDEBUG宏
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  add_definitions(-DDEBUG)
else()
  add_definitions(-DNDEBUG)
endif()

# 添加src子目录到项目中，子目录中也会对应有一个CMakeLists.txt
add_subdirectory(src)

if(BUILD_BURIED_EXAMPLES)
  add_subdirectory(examples)
endif()

if(BUILD_BURIED_TEST)
  include_directories(
    googletest/googletest
    googletest/googletest/include)
  add_subdirectory(googletest)
  add_subdirectory(tests)
endif()