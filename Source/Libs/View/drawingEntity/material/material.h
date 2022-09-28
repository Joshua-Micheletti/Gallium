#ifndef __MATERIAL__
#define __MATERIAL__

#include "GLAD/glad.h"
#include <string>

class Material {
    public:
        Material();
        std::string shader();
        Material* shader(std::string);
        
        std::string texture();
        Material* texture(std::string);
        void printFull();

    private:
        std::string shader_;
        std::string texture_;
};



#endif