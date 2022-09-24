#ifndef __DRAWINGENTITY__
#define __DRAWINGENTITY__

//#include "../global.h"
#include <string>

class DrawingEntity {
    public:
        DrawingEntity();
        std::string model();
        std::string material();

        void setModel(std::string);
        void setMaterial(std::string);

        void printFull();

    private:
        std::string model_;
        std::string material_;
};

#endif