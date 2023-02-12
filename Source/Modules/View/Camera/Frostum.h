#ifndef __FROSTUM__
#define __FROSTUM__

#include "../../Utils/Plane.h"

class Frostum {
    public:
        Frostum();
        
        Plane nearPlane();
        Plane farPlane();
        Plane top();
        Plane bottom();
        Plane left();
        Plane right();

        Frostum* nearPlane(Plane);
        Frostum* farPlane(Plane);
        Frostum* top(Plane);
        Frostum* bottom(Plane);
        Frostum* left(Plane);
        Frostum* right(Plane);

        bool isOnFrustum(glm::vec3, float);

    private:
        Plane m_top;
        Plane m_bottom;
        Plane m_right;
        Plane m_left;
        Plane m_far;
        Plane m_near;
};


#endif