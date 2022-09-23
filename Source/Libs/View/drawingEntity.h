#ifndef __DRAWINGENTITY_
#define __DRAWINGENTITY__

#include "model.h"
#include "material.h"

class DrawingEntity {
    public:
        DrawingEntity();
        Model* model();
        Material* material();

        void printFull();

    private:
        Model model_;
        Material material_;
};

#endif