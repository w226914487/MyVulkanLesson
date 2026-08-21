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


target_include_directories(${PROJECT_NAME} PUBLIC include)
#链接glfw
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan glfw)