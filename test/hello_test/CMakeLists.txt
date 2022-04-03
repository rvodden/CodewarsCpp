enable_testing()

add_executable(libhello_test hello_test.cpp)

target_link_libraries(libhello_test gtest_main)
target_link_libraries(libhello_test gmock_main)

include(GoogleTest)
gtest_discover_tests(libhello_test)
target_link_libraries(libhello_test libhello)