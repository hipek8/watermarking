set(CMAKE_VERBOSE_MAKEFILE ON)
cmake_minimum_required (VERSION 2.8.2)
project (watermark CXX C)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
ADD_DEFINITIONS(-std=c++1z)
include_directories(${CMAKE_SOURCE_DIR}/src)
find_package( OpenCV REQUIRED)
add_executable(decode ${SOURCE_FILES} main/decode.cpp)
add_executable(encode ${SOURCE_FILES} main/encode.cpp)
target_link_libraries(decode ${OpenCV_LIBS})
target_link_libraries(encode ${OpenCV_LIBS})




set (BUILD_TESTS FALSE)
if (BUILD_TESTS)
    configure_file(CMakeLists.txt.in
                   googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
     
    # Prevent GoogleTest from overriding our compiler/linker options
    # when building with Visual Studio
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
     
    # Add googletest directly to our build. This adds
    # the following targets: gtest, gtest_main, gmock
    # and gmock_main
    add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                     ${CMAKE_BINARY_DIR}/googletest-build)
     
    # The gtest/gmock targets carry header search path
    # dependencies automatically when using CMake 2.8.11 or
    # later. Otherwise we have to add them here ourselves.
    if (CMAKE_VERSION VERSION_LESS 2.8.11)
      include_directories("${gtest_SOURCE_DIR}/include"
                          "${gmock_SOURCE_DIR}/include")
    endif()
     
    file(GLOB_RECURSE TEST_FILES test/*.cpp)
    add_executable(Tests ${SOURCE_FILES} ${TEST_FILES} )
    # target_compile_definitions(Tests PRIVATE GOOGLE_UNIT_TEST=1)
    target_link_libraries(Tests gtest)
endif()
