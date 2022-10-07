#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>
#include <cmath>

extern int maxLength(std::vector<float>);
extern int countFaces(std::vector<float>);
extern void createBuffer(std::vector<float>, unsigned int*);
extern void readOBJMesh(std::string, std::vector<float>*, std::vector<float>*, std::vector<float>*);
extern void readOBJ(std::string, std::vector<std::vector<float>*>*, std::vector<std::vector<float>*>*, std::vector<std::vector<float>*>*, std::vector<std::string>*);
extern void readMTL(std::string, std::vector<std::string>*, std::vector<std::vector<float>*>*, std::vector<std::vector<float>*>*, std::vector<std::vector<float>*>*, std::vector<float>*);
extern void polarToCartesian(float, float, float*, float*);
extern int find(std::string, std::vector<std::string>);

extern std::string strRed;
extern std::string strGreen;
extern std::string strBlue;
extern std::string strNoColor;

extern bool updateResolution;
extern bool updated;


#endif