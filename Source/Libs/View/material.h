#ifndef __MATERIAL__
#define __MATERIAL__

#include "GLAD/glad.h"
#include <string>
#include "shader.h"

class Material {
    public:
        Material();
        Shader shader();

        void printFull();

    private:
        Shader shader_ = NULL;
};



#endif