project(CppPricingToolboxPython CXX)

file(GLOB_RECURSE TOOLBOX_PYTHON_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )

add_library(${PROJECT_NAME} SHARED ${TOOLBOX_PYTHON_SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${TOOLBOX_ROOT_DIR}/include)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${TOOLBOX_ROOT_DIR}/external)

if (MSVC)
    target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${TOOLBOX_ROOT_DIR}/external/python_36/win_include)
    target_link_libraries(${PROJECT_NAME} ${TOOLBOX_ROOT_DIR}/external/python_36/win_lib/python36.lib)
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${TOOLBOX_ROOT_DIR}/external/python_38/linux_include)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".pyd")
