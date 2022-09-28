#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>
#include "View/drawingEntity/drawingEntity.h"

extern int maxLength(std::vector<float>);
extern int countFaces(std::vector<float>);
extern void createBuffer(std::vector<float>, unsigned int*);
extern void readOBJ(std::string, std::vector<float>&, std::vector<float>&, std::vector<float>&);
extern void polarToCartesian(float, float, float*, float*);

extern std::string strRed;
extern std::string strGreen;
extern std::string strBlue;
extern std::string strNoColor;

extern bool updateResolution;


#endif