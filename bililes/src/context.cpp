#include "context.hpp"
#include <iostream>
#include "render2d.hpp"


namespace render2d{
    std::unique_ptr<Context> Context::instance_ = nullptr;
    
    void Context::Init(const std::vector<const char*>& extensions,CreateSurfaceFunc func,int w,int h){
        if(!instance_){
            instance_.reset(new Context(extensions,func,w,h));
        }
    };
    void Context::Quit(){instance_.reset();};

    Context& Context::GetInstance(){
        return *instance_;
    };
    
    Context::Context(const std::vector<const char*>& extensions,CreateSurfaceFunc func,int w,int h){
        createInstance(extensions,func,w,h);
        pickUpPhysicalDevice();
        queryQueueFamilyIndices();
        surface = func(instance);
        //创建逻辑设备
        createDevice();
        getQueues();
        swapchain.reset(new Swapchain(w,h));
    };
    Context::~Context(){
        swapchain.reset();  
        device.destroy();
        instance.destroy();
    };

    void Context::createInstance(const std::vector<const char*>& extensions,CreateSurfaceFunc func,int w,int h){
        vk::InstanceCreateInfo creatInfo;
        vk::ApplicationInfo appInfo;
        appInfo.setApiVersion(VK_API_VERSION_1_4);
        creatInfo.setPApplicationInfo(&appInfo);
        //开启调试层
        std::vector<const char*> layers ={"VK_LAYER_KHRONOS_validation"};
        creatInfo.setPEnabledLayerNames(layers)
                 .setPEnabledExtensionNames(extensions);
        instance = vk::createInstance(creatInfo);
    };
    void Context::pickUpPhysicalDevice(){
        auto devices = instance.enumeratePhysicalDevices();
        for (auto& device:devices){
            auto feature = device.getFeatures();
        }
        phyDevice = devices[0];
        std::cout<<phyDevice.getProperties().deviceName<<std::endl;
    };
    void Context::createDevice(){
        vk::DeviceCreateInfo createInfo;
        std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
        float priorities = 1.0;
        if(queueFamilyIndices.presentQueue.value() == queueFamilyIndices.graphicsQueue.value()){
            vk::DeviceQueueCreateInfo queueCreateInfo;
            queueCreateInfo.setPQueuePriorities(&priorities)
                       .setQueueCount(1)
                       .setQueueFamilyIndex(queueFamilyIndices.graphicsQueue.value());
            queueCreateInfos.push_back(std::move(queueCreateInfo));
        }else{
            vk::DeviceQueueCreateInfo queueCreateInfo;
            queueCreateInfo.setPQueuePriorities(&priorities)
                       .setQueueCount(1)
                       .setQueueFamilyIndex(queueFamilyIndices.graphicsQueue.value());
            queueCreateInfos.push_back(queueCreateInfo);
            queueCreateInfo.setPQueuePriorities(&priorities)
                       .setQueueCount(1)
                       .setQueueFamilyIndex(queueFamilyIndices.presentQueue.value());
            queueCreateInfos.push_back(queueCreateInfo);}
        createInfo.setQueueCreateInfos(queueCreateInfos);
        device = phyDevice.createDevice(createInfo);
    };
    void Context::queryQueueFamilyIndices(){
        //查询物理设备中队列家族属性
        auto properties = phyDevice.getQueueFamilyProperties();
        for (int i=0;i<properties.size();i++){
            const auto& property = properties[i];
            if(property.queueFlags | vk::QueueFlagBits::eGraphics){
                queueFamilyIndices.graphicsQueue = i;
            }
            if(phyDevice.getSurfaceSupportKHR(i,surface)){
            queueFamilyIndices.presentQueue = i;
            }
            if(queueFamilyIndices){
                break;
            }
        }
        
    };
    void Context::getQueues(){
        graphicsQueue = device.getQueue(queueFamilyIndices.graphicsQueue.value(),0);
        presentQueue = device.getQueue(queueFamilyIndices.presentQueue.value(),0);
    };
}