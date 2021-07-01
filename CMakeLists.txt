cmake_minimum_required(VERSION 3.11-3.18)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(ddhorbot VERSION 0.1)

find_file(WINDOWS_HEADER windows.h)
if(NOT WINDOWS_HEADER)
  message(FATAL_ERROR "Can't find windows.h!")
endif()

#Generate PDB

file(GLOB_RECURSE SOURCE_FILES *.cpp)
add_library(ddhorbot SHARED ${SOURCE_FILES})

#add_compile_options("/Debug /Zi")
add_compile_definitions(WIN32_LEAN_AND_MEAN)

target_include_directories(${PROJECT_NAME} PRIVATE 
    Dependencies/cocos-headers/cocos2dx
    Dependencies/cocos-headers/cocos2dx/include
    Dependencies/cocos-headers/cocos2dx/kazmath/include
    Dependencies/cocos-headers/cocos2dx/platform/win32
    Dependencies/cocos-headers/cocos2dx/platform/third_party/win32
    Dependencies/cocos-headers/cocos2dx/platform/third_party/win32/OGLES
    Dependencies/cocos-headers/extensions
)

target_include_directories(${PROJECT_NAME} PRIVATE Dependencies/)
target_include_directories(${PROJECT_NAME} PRIVATE Dependencies/gd)
target_include_directories(${PROJECT_NAME} PRIVATE Bot/)
target_include_directories(${PROJECT_NAME} PRIVATE IOManager/)
target_include_directories(${PROJECT_NAME} PRIVATE Cheats/)
target_include_directories(${PROJECT_NAME} PRIVATE GameController/)

target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/Dependencies/cocos-headers/cocos2dx/libcocos2d.lib)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/Dependencies/cocos-headers/extensions/libExtensions.lib)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/Dependencies/minhook/minhook.x32.lib)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/Dependencies/fmt/fmt.lib)