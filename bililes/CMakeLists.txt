cmake_minimum_required(VERSION 4.0)
project(bililes)


file(GLOB_RECURSE srcs CONFIGURE_DEPENDS
    src/*.cpp
    include/*.h
)


add_executable(
    ${PROJECT_NAME}
    ${srcs}
)
find_program(GLSLC_PROGRAM glslc REQUIRED)
execute_process(COMMAND ${GLSLC_PROGRAM} ${PROJECT_SOURCE_DIR}/shader/shader.vert -o ${PROJECT_SOURCE_DIR}/vert.spv)
execute_process(COMMAND ${GLSLC_PROGRAM} ${PROJECT_SOURCE_DIR}/shader/shader.frag -o ${PROJECT_SOURCE_DIR}/frag.spv)


target_include_directories(${PROJECT_NAME} PUBLIC include)
#链接glfw
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan glfw)
#自动添加文件
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/vert.spv
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/vert.spv
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/frag.spv
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/frag.spv
)