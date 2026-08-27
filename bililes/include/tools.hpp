#pragma once
#include<functional>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include "vulkan/vulkan.hpp"
using CreateSurfaceFunc = std::function<vk::SurfaceKHR(vk::Instance)>;
namespace render2d{
std::string ReadWholeFile(const std::string& filename);
}