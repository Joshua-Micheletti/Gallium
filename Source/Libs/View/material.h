#ifndef __MATERIAL__
#define __MATERIAL__

#include "GLAD/glad.h"
#include <string>

class Material {
    public:
        Material();
        std::string shader();
        void shader(std::string);
        void printFull();

    private:
        std::string shader_;
};



#endif