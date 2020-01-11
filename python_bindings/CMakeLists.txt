project(CppPricingToolboxPython CXX)

file(GLOB_RECURSE TOOLBOX_PYTHON_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )

add_library(${PROJECT_NAME} SHARED ${TOOLBOX_PYTHON_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${TOOLBOX_ROOT_DIR}/external/python_36/lib/python36.lib)
target_include_directories(${PROJECT_NAME} PUBLIC ${TOOLBOX_ROOT_DIR}/include)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${TOOLBOX_ROOT_DIR}/external)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${TOOLBOX_ROOT_DIR}/external/python_36/include)
                                           
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".pyd")
