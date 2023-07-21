#ifndef __FROSTUM__
#define __FROSTUM__

#include "../Model/Plane/Plane.h"

// class for a frostum model (used for camera frostum culling)
class Frostum {
    public:
        // constructor
        Frostum();
        
        // getters for the planes that make up the frostum
        Plane nearPlane();
        Plane farPlane();
        Plane top();
        Plane bottom();
        Plane left();
        Plane right();

        // setters for the planes that make up the frostum
        Frostum* nearPlane(Plane);
        Frostum* farPlane(Plane);
        Frostum* top(Plane);
        Frostum* bottom(Plane);
        Frostum* left(Plane);
        Frostum* right(Plane);

        // method for checking if a mesh is inside the frostum
        bool isOnFrostum(glm::vec3, float);

    private:
        // planes that make up the frostum
        Plane m_top;
        Plane m_bottom;
        Plane m_right;
        Plane m_left;
        Plane m_far;
        Plane m_near;
};


#endif