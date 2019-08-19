project(CppPricingToolbox_SampleScripts CXX)

file(GLOB_RECURSE TOOLBOX_SAMPLE_SCRIPT_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )

message(STATUS "===== C++ Sample Scripts:")
foreach(SRC_FILE ${TOOLBOX_SAMPLE_SCRIPT_SOURCE_FILES})
    get_filename_component(SRC_NAME ${SRC_FILE} NAME_WE)
    message(STATUS "=====   ${SRC_NAME}" )

    add_executable(${SRC_NAME} ${SRC_FILE})
    target_include_directories(${SRC_NAME} PUBLIC ${TOOLBOX_ROOT_DIR}/include)
endforeach()
