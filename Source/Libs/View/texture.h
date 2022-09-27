#ifndef __TEXTURE__
#define __TEXTURE__

#include <string>
#include <GLAD/glad.h>


class Texture {
    public:
        void loadTexture(std::string);
        unsigned int id();
        void printFull();

    private:
        unsigned int id_;
};



#endif