#include "context.hpp"
#include "render2d.hpp"
//#include <STB/stb_image.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <iostream>
int main(){
    
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(1280,720,"Vulkan",nullptr,nullptr);
    //获取extensions
    uint32_t extensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);
    std::vector<const char*> extensions(glfwExtensions,glfwExtensions + extensionCount);
    

    render2d::Init(extensions,[&](vk::Instance instance){
        VkSurfaceKHR surface;
        VkResult result = glfwCreateWindowSurface(instance,window,nullptr,&surface);
        return surface;},1280,720); 
    auto& renderer = render2d::GetRenderer();
    while(!glfwWindowShouldClose(window)){
        //glfwPollEvents();
        renderer.Render();
    }
    render2d::Quit();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}