#pragma once
#include<vulkan/vulkan.hpp>
#include"context.hpp"
#include<functional>
using CreateSurfaceFunc = std::function<vk::SurfaceKHR(vk::Instance)>;
namespace render2d{

    void Init(const std::vector<const char*>& extensions,CreateSurfaceFunc func,int w,int h);
    void Quit();


}
