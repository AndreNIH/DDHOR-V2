cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/deps/vcpkg/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(DDHORV3 VERSION 0.1.0)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)


file(GLOB_RECURSE SRC_FILES src/*.cpp)

#add_executable(DDHORV3 ${SRC_FILES})
add_library(DDHORV3 SHARED ${SRC_FILES})
add_subdirectory(deps/cocos-headers)
add_subdirectory(deps/mat-dash)
add_subdirectory(deps/minhook)

target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt-header-only)
target_link_libraries(${PROJECT_NAME} PUBLIC cocos2d)
target_link_libraries(${PROJECT_NAME} PUBLIC matdash)
target_link_libraries(${PROJECT_NAME} PUBLIC minhook)

set(GD_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/deps/gd
    ${CMAKE_CURRENT_LIST_DIR}/deps/gd/include
)

target_include_directories(${PROJECT_NAME} PUBLIC ${GD_HEADERS} src/)

add_custom_command(TARGET ${PROJECT_NAME}
    PRE_BUILD
    COMMAND taskkill /f /fi "pid gt 0" /im GeometryDash.exe
)