#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


extern int maxLength(std::vector<float>);
extern int countFaces(std::vector<float>);
extern void createBuffer(std::vector<float>, unsigned int*);
extern bool readOBJMesh(std::string, std::vector<float>*, std::vector<float>*, std::vector<float>*);
extern bool readOBJ(std::string, std::vector<std::vector<float>*>*, std::vector<std::vector<float>*>*, std::vector<std::vector<float>*>*, std::vector<std::string>*);
extern bool readMTL(std::string, std::vector<std::string>*, std::vector<std::vector<float>*>*, std::vector<std::vector<float>*>*, std::vector<std::vector<float>*>*, std::vector<float>*);
extern void polarToCartesian(float, float, float*, float*);
extern int find(std::string, std::vector<std::string>);
extern const char** stringVectorToCArray(std::vector<std::string>);

extern std::string strRed;
extern std::string strGreen;
extern std::string strBlue;
extern std::string strNoColor;

extern bool updateResolution;
extern bool updated;


#endif