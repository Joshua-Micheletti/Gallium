#include "RenderTexture.h"

RenderTexture::RenderTexture() {
    this->m_general = "T_Default";
    this->m_diffuse = "";
    this->m_specular = "";
}

std::string RenderTexture::general() {
    return(this->m_general);
}
RenderTexture* RenderTexture::general(std::string t) {
    this->m_general = t;
    return(this);
}

std::string RenderTexture::diffuse() {
    if (this->m_diffuse.size() == 0) {
        return(this->m_general);
    } else {
        return(this->m_diffuse);
    }
}
RenderTexture* RenderTexture::diffuse(std::string t) {
    this->m_diffuse = t;
    return(this);
}

std::string RenderTexture::specular() {
    if (this->m_specular.size() == 0) {
        return(this->m_general);
    } else {
        return(this->m_specular);
    }
}
RenderTexture* RenderTexture::specular(std::string t) {
    this->m_specular = t;
    return(this);
}