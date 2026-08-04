#include "context.hpp"
#include <iostream>


namespace render2d{
    std::unique_ptr<Context> Context::instance_ = nullptr;
    
    void Context::Init(){
        if(!instance_){
            instance_.reset(new Context);
        }
    };
    void Context::Quit(){instance_.reset();};

    Context& Context::GetInstance(){
        return *instance_;
    };
    
    Context::Context(){
        createInstance();
        pickUpPhysicalDevice();
        queryQueueFamilyIndices();
        //创建逻辑设备
        createDevice();
        getQueues();
    };
    Context::~Context(){  
        device.destroy();
        //instance.destroy();
    };

    void Context::createInstance(){
        vk::InstanceCreateInfo creatInfo;
        vk::ApplicationInfo appInfo;
        appInfo.setApiVersion(VK_API_VERSION_1_4);
        creatInfo.setPApplicationInfo(&appInfo);
        //开启调试层
        std::vector<const char*> layers ={"VK_LAYER_KHRONOS_validation"};
        creatInfo.setPEnabledLayerNames(layers);
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
        vk::DeviceQueueCreateInfo queueCreateInfo;
        float priorities = 1.0;
        queueCreateInfo.setPQueuePriorities(&priorities)
                       .setQueueCount(1)
                       .setQueueFamilyIndex(queueFamilyIndices.graphicsQueue.value());

        createInfo.setQueueCreateInfos(queueCreateInfo);
        device = phyDevice.createDevice(createInfo);
    };
    void Context::queryQueueFamilyIndices(){
        //查询物理设备中队列家族属性
        auto properties = phyDevice.getQueueFamilyProperties();
        for (int i=0;i<properties.size();i++){
            const auto& property = properties[i];
            if(property.queueFlags | vk::QueueFlagBits::eGraphics){
                queueFamilyIndices.graphicsQueue = i;
                break;
            }
        }

    };
    void Context::getQueues(){
        graphicsQueue = device.getQueue(queueFamilyIndices.graphicsQueue.value(),0);
    };
}