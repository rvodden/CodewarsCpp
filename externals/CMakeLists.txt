include(FetchContent)

### Google Test ###

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)


set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

target_compile_options(gmock PRIVATE -fsanitize=undefined)
target_link_options(gmock PRIVATE -fsanitize=undefined)
target_compile_options(gtest PRIVATE -fsanitize=undefined)
target_link_options(gtest PRIVATE -fsanitize=undefined)

