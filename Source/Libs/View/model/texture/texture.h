#ifndef __TEXTURE__
#define __TEXTURE__

#include <string>
#include <vector>
#include <GLAD/glad.h>

class Texture {
    public:
        void loadTexture(std::string);
        void loadCubemap(std::vector<std::string>);
        unsigned int id();
        void printFull();
        GLenum type();

    private:
        unsigned int id_;
        GLenum type_;
};

#endif