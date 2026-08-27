#include "render2d.hpp"
#include "tools.hpp"

namespace render2d{
    void Init(const std::vector<const char*>& extensions,CreateSurfaceFunc func,int w,int h){
        Context::Init(extensions,func);
        Context::GetInstance().InitSwapchain(w,h);
        Shader::Init(ReadWholeFile("./vert.spv"),ReadWholeFile("./frag.spv"));
    };
    void Quit(){
        Context::GetInstance().DestroySwapchain();
        Shader::Quit();
        Context::Quit();
    };


}