project(CppPricingToolbox_UnitTests CXX)

file(GLOB_RECURSE TOOLBOX_UNIT_TEST_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/individual/*.cpp )

message(STATUS "===== C++ Unit Tests:")
foreach(SRC_FILE ${TOOLBOX_UNIT_TEST_SOURCE_FILES})
    get_filename_component(SRC_NAME ${SRC_FILE} NAME_WE)
    message(STATUS "=====   ${SRC_NAME}" )
endforeach()

add_executable(${PROJECT_NAME} src/UnitTest_Main.cpp ${TOOLBOX_UNIT_TEST_SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${TOOLBOX_ROOT_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${TOOLBOX_ROOT_DIR}/external)
