project(CppPricingToolbox_UnitTests CXX)

file(GLOB_RECURSE TOOLBOX_UNIT_TEST_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

file(GLOB_RECURSE TOOLBOX_CATCH2_SOURCE_FILES
     ${TOOLBOX_ROOT_DIR}/external/catch2/*.cpp)

message(STATUS "===== C++ Unit Tests:")
foreach(SRC_FILE ${TOOLBOX_UNIT_TEST_SOURCE_FILES})
    get_filename_component(SRC_NAME ${SRC_FILE} NAME_WE)
    message(STATUS "=====   ${SRC_NAME}")
endforeach()

add_executable(UnitTests ${TOOLBOX_CATCH2_SOURCE_FILES} ${TOOLBOX_UNIT_TEST_SOURCE_FILES})
target_include_directories(UnitTests PUBLIC ${TOOLBOX_ROOT_DIR}/include)
target_include_directories(UnitTests PUBLIC ${TOOLBOX_ROOT_DIR}/external)
