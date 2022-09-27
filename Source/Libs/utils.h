#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>
#include <string>
#include <glad/glad.h>
#include <map>
#include "View/drawingEntity.h"

extern int maxLength(std::vector<float>);
extern int countFaces(std::vector<float>);
extern void createBuffer(std::vector<float>, unsigned int*);
extern void readOBJ(std::string, std::vector<float>&, std::vector<float>&, std::vector<float>&);

extern std::string strRed;
extern std::string strGreen;
extern std::string strBlue;
extern std::string strNoColor;

#endif