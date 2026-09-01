#pragma once

#include <vulkan/vulkan.hpp>
#include <memory>
#include <optional>
#include "swapchain.hpp"
#include "tools.hpp"
#include "renderprocess.hpp"
#include "renderer.hpp"

namespace render2d{
    class Context final{
    public:
        static void Init(const std::vector<const char*>& extensions,CreateSurfaceFunc func);
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
        std::unique_ptr<RenderProcess> renderProcess;
        std::unique_ptr<Renderer> renderer;
        struct QueueFamilyIndices {std::optional<uint32_t> graphicsQueue;
                                   std::optional<uint32_t> presentQueue;
                                   operator bool() const {return graphicsQueue.has_value() && presentQueue.has_value();}
        };
        QueueFamilyIndices queueFamilyIndices;
        void InitSwapchain(int w,int h){
            swapchain.reset(new Swapchain(w,h));
        }
        void DestroySwapchain(){
            swapchain.reset();
        };
        void InitRenderer(){
            renderer.reset(new Renderer);
        };

    private:
        Context(const std::vector<const char*>& extensions,CreateSurfaceFunc func);
        static std::unique_ptr<Context> instance_;
        void createInstance(const std::vector<const char*>& extensions,CreateSurfaceFunc func);
        void pickUpPhysicalDevice();
        void createDevice();
        void queryQueueFamilyIndices();
        void getQueues();
    };


}