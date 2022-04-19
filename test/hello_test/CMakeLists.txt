enable_testing()

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
add_executable(libhello_test ${SOURCE_FILES})

target_link_libraries(libhello_test gtest_main)
target_link_libraries(libhello_test gmock_main)

target_compile_options(libhello_test PRIVATE -fsanitize=undefined)
target_link_options(libhello_test PRIVATE -fsanitize=undefined)

include(GoogleTest)
gtest_discover_tests(libhello_test XML_OUTPUT_DIR report)
target_link_libraries(libhello_test libhello)