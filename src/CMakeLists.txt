# 表示项目中的头文件只会被包含以此
include_guard(GLOBAL)

include_directories(third_party/spdlog/include)

add_definitions(-DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)
add_subdirectory(third_party/spdlog)

# configure_file(${CMAKE_CURRENT_SOURCE_DIR}/buried_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/buried_config.h)

set(DB_SRCS third_party/sqlite/sqlite3.c database/database.cc)

set(BURIED_SRC
  buried.cc
  buried_core.cc)

set(MODULE_NAME "Buried")

message(STATUS "libs ${LIBS}")

# 编译动态库
if(BUILD_BURIED_SHARED_LIBS)
  add_library(${MODULE_NAME} SHARED $(BURIED_SRCS))
  target_link_libraries(${MODULE_NAME} PRIVATE ${LIBS} spdlog)
endif()

# 编译静态库
if(BUILD_BURIED_STATIC_LIBS)
  add_library(${MODULE_NAME}_static STATIC ${BURIED_SRCS})
  target_link_libraries(${MODULE_NAME} PRIVATE ${LIBS} spdlog)
endif()
