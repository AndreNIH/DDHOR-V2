cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/deps/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(DDHORV3 VERSION 0.1.0)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

enable_testing()

file(GLOB_RECURSE SRC_FILES src/*.cpp)
#add_executable(DDHORV3 ${SRC_FILES})
add_library(DDHORV3 SHARED ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt-header-only)

#add_subdirectory(tests)