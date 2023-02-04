#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


extern int maxLength(std::vector<float>);
extern int countFaces(std::vector<float>);
extern void createBuffer(std::vector<float>, unsigned int*);
extern void createIndexBuffer(std::vector<unsigned int>, unsigned int*);
extern bool readOBJMesh(std::string, std::vector<float>*, std::vector<float>*, std::vector<float>*);
extern bool readOBJ(std::string, std::vector<std::vector<float>*>*, std::vector<std::vector<float>*>*, std::vector<std::vector<float>*>*, std::vector<std::string>*);
extern bool readMTL(std::string, std::vector<std::string>*, std::vector<std::vector<float>*>*, std::vector<std::vector<float>*>*, std::vector<std::vector<float>*>*, std::vector<float>*);
extern void polarToCartesian(float, float, float*, float*);
extern int find(std::string, std::vector<std::string>);
extern const char** stringVectorToCArray(std::vector<std::string>);
extern glm::vec3 averageVector3f(std::vector<float>);
extern float maxDistanceVector3f(glm::vec3, std::vector<float>);

extern std::string strRed;
extern std::string strGreen;
extern std::string strBlue;
extern std::string strYellow;
extern std::string strNoColor;

extern bool updateResolution;
extern bool updated;


#endif