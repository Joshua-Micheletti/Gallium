#include "Frostum.h"

Frostum::Frostum() {
}



Plane Frostum::nearPlane() {
    return(this->m_near);
}
Plane Frostum::farPlane() {
    return(this->m_far);
}
Plane Frostum::top() {
    return(this->m_top);
}
Plane Frostum::bottom() {
    return(this->m_bottom);
}
Plane Frostum::left() {
    return(this->m_left);
}
Plane Frostum::right() {
    return(this->m_right);
}

Frostum* Frostum::nearPlane(Plane plane) {
    this->m_near = plane;
    return(this);
}
Frostum* Frostum::farPlane(Plane plane) {
    this->m_far = plane;
    return(this);
}
Frostum* Frostum::top(Plane plane) {
    this->m_top = plane;
    return(this);
}
Frostum* Frostum::bottom(Plane plane) {
    this->m_bottom = plane;
    return(this);
}
Frostum* Frostum::left(Plane plane) {
    this->m_left = plane;
    return(this);
}
Frostum* Frostum::right(Plane plane) {
    this->m_right = plane;
    return(this);
}