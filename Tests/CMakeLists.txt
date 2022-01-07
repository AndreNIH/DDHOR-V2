cmake_minimum_required(VERSION 3.10)

set(TEST_FILES SerderTest.cc)
add_executable(DDHORTests ${TEST_FILES})

find_package(GTest CONFIG REQUIRED)

target_link_libraries(DDHORTests PRIVATE GTest::gtest_main)
target_link_libraries(DDHORTests PRIVATE DDHORV3)

include(GoogleTest)
gtest_discover_tests(DDHORTests)
