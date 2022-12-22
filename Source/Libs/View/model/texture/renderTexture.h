#ifndef __RENDERTEXTURE__
#define __RENDERTEXTURE__

#include <string>

class RenderTexture {
    public:
        RenderTexture();
        std::string general();
        RenderTexture* general(std::string);
        std::string diffuse();
        RenderTexture* diffuse(std::string);
        std::string specular();
        RenderTexture* specular(std::string);

    private:
        std::string general_;
        std::string diffuse_;
        std::string specular_;
};


#endif