enable_testing()

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
add_executable(libhello_test ${SOURCE_FILES})

target_link_libraries(libhello_test gtest_main)
target_link_libraries(libhello_test gmock_main)

include(GoogleTest)
gtest_discover_tests(libhello_test XML_OUTPUT_DIR report EXTRA_ARGS --gtest_catch_exceptions=0)
target_compile_options(libhello_test PRIVATE -W)
target_link_libraries(libhello_test libhello)