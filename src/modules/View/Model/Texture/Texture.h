#ifndef __TEXTURE__
#define __TEXTURE__

#include <string>
#include <vector>

#include <glad/glad.h>

class Texture {
    public:
        void loadTexture(std::string);
        void loadCubemap(std::vector<std::string>);
        unsigned int id();
        void printFull();
        GLenum type();

    private:
        unsigned int m_id;
        GLenum m_type;
};

#endif