cmake_minimum_required (VERSION 3.13)

project(CppPricingToolbox CXX)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE TOOLBOX_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

message(STATUS "===== Cpp Scripts:")
foreach(SRC_FILE ${TOOLBOX_SOURCE_FILES})
    get_filename_component(SRC_NAME ${SRC_FILE} NAME_WE)
    message(STATUS "=====   ${SRC_NAME}" )

    add_executable(${SRC_NAME} ${SRC_FILE})
    target_include_directories(${SRC_NAME} PUBLIC include)
endforeach()
