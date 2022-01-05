cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/deps/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(DDHORV3 VERSION 0.1.0)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(DDHORV3 ${SRC_FILES})

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json nlohmann_json::nlohmann_json)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt-header-only)
