project(Google_tests)

add_subdirectory(lib)
find_package(GTest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runAllTests runAllTest.cpp Enemy_test.cpp Map_test.cpp Item_test.cpp)
target_link_libraries(runAllTests gtest gtest_main core)
