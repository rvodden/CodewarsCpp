file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
add_library(maze ${SOURCE_FILES})

target_link_libraries(maze PRIVATE compiler_flags)
target_include_directories(maze INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)
target_compile_definitions(maze PRIVATE "EXPORTING_MAZE")

install(TARGETS maze DESTINATION lib EXPORT maze_targets)
install(FILES hello.h DESTINATION include)