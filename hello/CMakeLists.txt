file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
add_library(libhello ${SOURCE_FILES})

target_link_libraries(libhello PRIVATE compiler_flags)
target_include_directories(libhello INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)
target_compile_definitions(libhello PRIVATE "EXPORTING_LIBHELLO")

install(TARGETS libhello DESTINATION lib EXPORT libhello_targets)
install(FILES hello.h DESTINATION include)