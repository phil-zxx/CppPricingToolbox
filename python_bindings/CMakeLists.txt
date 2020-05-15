project(CppPricingToolboxPython CXX)

file(GLOB_RECURSE TOOLBOX_PYTHON_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${TOOLBOX_PYTHON_SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${TOOLBOX_ROOT_DIR}/include)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${TOOLBOX_ROOT_DIR}/external)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "===== Using Windows Build Settings for Python Bindings")
    target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${TOOLBOX_ROOT_DIR}/external/python_36/win_include)
    target_link_libraries(${PROJECT_NAME} ${TOOLBOX_ROOT_DIR}/external/python_36/win_lib/python36.lib)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "===== Using Windows Build Settings for Python Bindings")
    target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${TOOLBOX_ROOT_DIR}/external/python_38/linux_include)
else()
    message(FATAL_ERROR "===== Compiler ${CMAKE_CXX_COMPILER_ID} not supported for Python Bindings")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".pyd")
