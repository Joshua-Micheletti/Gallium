#include "renderTexture.h"

RenderTexture::RenderTexture() {
    this->general_ = "T_Default";
    this->diffuse_ = "";
    this->specular_ = "";
}

std::string RenderTexture::general() {
    return(this->general_);
}
RenderTexture* RenderTexture::general(std::string t) {
    this->general_ = t;
    return(this);
}

std::string RenderTexture::diffuse() {
    if (this->diffuse_.size() == 0) {
        return(this->general_);
    } else {
        return(this->diffuse_);
    }
}
RenderTexture* RenderTexture::diffuse(std::string t) {
    this->diffuse_ = t;
    return(this);
}

std::string RenderTexture::specular() {
    if (this->specular_.size() == 0) {
        return(this->general_);
    } else {
        return(this->specular_);
    }
}
RenderTexture* RenderTexture::specular(std::string t) {
    this->specular_ = t;
    return(this);
}