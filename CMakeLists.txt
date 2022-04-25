### General Settings ###

cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(codewars VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

#set(CMAKE_CXX_CLANG_TIDY clang-tidy)

### Define Options ###

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# enable sanitization
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -fsanitize=undefined")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fsanitize=undefined")

### Compiler Options ###

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_17)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(compiler_flags INTERFACE
        "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused;-O2>>"
        "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
        )

### Subdirectories ###

add_subdirectory(externals)
add_subdirectory(hello)
add_subdirectory(maze)
add_subdirectory(test/hello_test)
add_subdirectory(test/maze_test)

### Configuration Files ###

configure_file(config.h.in config.h)

### Target: codewars ###

add_executable(codewars src/main.cpp)
target_link_libraries(codewars PRIVATE compiler_flags)
target_link_libraries(codewars PUBLIC libhello)
target_include_directories(codewars PUBLIC "${PROJECT_BINARY_DIR}")

enable_testing()

### Installation ###

install(TARGETS codewars DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)
install(EXPORT libhello_targets FILE libhello_targets.cmake DESTINATION lib/cmake/libhello_targets)

### Packaging ###

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${codewars_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${codewars_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${codewars_VERSION_PATCH}")
include(CPack)

### Exporting ###

include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/libhello_config.cmake"
        INSTALL_DESTINATION "lib/cmake/example"
        NO_SET_AND_CHECK_MACRO
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
        )
# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/libhello_config_version.cmake"
        VERSION "${codewars_VERSION_MAJOR}.${codewars_VERSION_MINOR}.${codewars_VERSION_PATCH}"
        COMPATIBILITY AnyNewerVersion
)

# install the configuration file
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/libhello_config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/libhello_config_version.cmake
        DESTINATION lib/cmake/libhello
        )

export(EXPORT libhello_targets FILE "${CMAKE_CURRENT_BINARY_DIR}/libhello_targets.cmake")