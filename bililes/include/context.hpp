#pragma once

#include <vulkan/vulkan.hpp>
#include <memory>
#include <optional>
#include "render2d.hpp"
#include "swapchain.hpp"

namespace render2d{
    class Context final{
    public:
        static void Init(const std::vector<const char*>& extensions,CreateSurfaceFunc func,int w,int h);
        static void Quit();
        static Context& GetInstance();
        ~Context();
        vk::Instance instance;
        vk::PhysicalDevice phyDevice;
        vk::Device device;
        vk::Queue graphicsQueue;
        vk::Queue presentQueue;
        vk::SurfaceKHR surface;
        std::unique_ptr<Swapchain> swapchain;
        struct QueueFamilyIndices {std::optional<uint32_t> graphicsQueue;
                                   std::optional<uint32_t> presentQueue;
                                   operator bool() const {graphicsQueue.has_value() && presentQueue.has_value();}
        };
        QueueFamilyIndices queueFamilyIndices;
    private:
        Context(const std::vector<const char*>& extensions,CreateSurfaceFunc func,int w,int h);
        static std::unique_ptr<Context> instance_;
        void createInstance(const std::vector<const char*>& extensions,CreateSurfaceFunc func,int w,int h);
        void pickUpPhysicalDevice();
        void createDevice();
        void queryQueueFamilyIndices();
        void getQueues();
    };


}