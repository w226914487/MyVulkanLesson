#pragma once

#include <vulkan/vulkan.hpp>
#include <memory>
#include <optional>

namespace render2d{
    class Context final{
    public:
        static void Init();
        static void Quit();
        static Context& GetInstance();
        ~Context();
        vk::Instance instance;
        vk::PhysicalDevice phyDevice;
        vk::Device device;
        vk::Queue graphicsQueue;
        struct QueueFamilyIndices {std::optional<uint32_t> graphicsQueue;};
        QueueFamilyIndices queueFamilyIndices;
    private:
        Context();
        static std::unique_ptr<Context> instance_;
        void createInstance();
        void pickUpPhysicalDevice();
        void createDevice();
        void queryQueueFamilyIndices();
        void getQueues();
    };


}