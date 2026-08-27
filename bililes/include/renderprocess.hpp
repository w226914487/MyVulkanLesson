#pragma once
#include <vulkan/vulkan.hpp>

namespace render2d{
    class RenderProcess {
        public:
            vk::Pipeline pipeline;
            void InitPipeline(int width,int height);
            void DestroyPipeline();
        private:
            //std::unique_ptr<RenderProcess> renderprocess;    
    };

}