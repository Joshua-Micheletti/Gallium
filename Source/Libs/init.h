#ifndef __INIT__
#define __INIT__

//#include <SFML\Graphics.hpp>
#include "GLFW\glfw3.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
//#include <glad\glad.h>
#include <vector>
#include "entity.h"
#include "shader.h"
#include "camera.h"

typedef struct buttons{
  bool backslash = false;
  bool A = false;
  bool B = false;
  bool C = false;
  bool D = false;
  bool E = false;
  bool F = false;
  bool G = false;
  bool H = false;
  bool I = false;
  bool J = false;
  bool K = false;
  bool L = false;
  bool M = false;
  bool N = false;
  bool O = false;
  bool P = false;
  bool Q = false;
  bool R = false;
  bool S = false;
  bool T = false;
  bool U = false;
  bool V = false;
  bool W = false;
  bool X = false;
  bool Y = false;
  bool Z = false;
  bool LAlt = false;
} buttons_t;

typedef enum {
  base,
  wireframe,
  vertices
} renderMode_t;

//// global variables
////extern GLFWwindow *window;

extern unsigned int screenWidth;
extern unsigned int screenHeight;
extern bool vsync;
extern bool fullscreen;

extern glm::mat4 Projection;
extern glm::mat4 Projection2;
extern glm::mat4 world_model;

extern Camera camera;
extern Camera camera2;

extern buttons_t press;
extern renderMode_t renderMode;

extern bool displayInfo;
extern bool freeMouse;
extern bool drawOBB;
extern bool drawAABB1;
extern bool drawAABB2;
extern bool drawAABB3;
extern bool drawAABB4;
extern bool drawBS;
extern bool drawBS2;
extern bool drawBS3;
extern bool doReflection;

////extern sf::Vector2i center;

extern int defaultCamera;

extern std::vector<Entity *> entityBuffer;
extern std::vector<Shader> shaderBuffer;
extern std::vector<Camera *> cameraBuffer;
extern std::vector<glm::mat4> projectionBuffer;

extern Entity *light;

extern GLFWwindow *setup();
extern GLFWwindow *initGLFW_OpenGL(std::string, int);

//extern GLenum glCheckError_(const char*, int);

#endif
