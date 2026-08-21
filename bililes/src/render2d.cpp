#include"render2d.hpp"

namespace render2d{
    void Init(const std::vector<const char*>& extensions,CreateSurfaceFunc func,int w,int h){
        Context::Init(extensions,func);
        Context::GetInstance().InitSwapchain(w,h);


    };
    void Quit(){
        Context::Quit();
    };


}