#pragma once
#include <vulkan/vulkan.hpp>

namespace render2d{
    class RenderProcess {
        public:
            vk::Pipeline pipeline;
            vk::PipelineLayout layout;
            vk::RenderPass renderPass;

            ~RenderProcess();

            void InitLayout();
            void InitRenderPass();
            void InitPipeline(int width,int height);
            void DestroyLayout();
        private:
            //std::unique_ptr<RenderProcess> renderprocess;    
    };

}