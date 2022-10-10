#ifndef __GLOBAL__
#define __GLOBAL__

#include "View/window/window.h"
#include "View/renderer/rendererManager.h"


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
  bool LALT = false;
  bool LSHIFT = false;
  bool SPACE = false;
  bool LCTRL = false;
} buttons_t;

typedef enum {
  base,
  wireframe,
  vertices
} renderMode_t;


extern unsigned int screenWidth;
extern unsigned int screenHeight;
extern unsigned int windowWidth;
extern unsigned int windowHeight;

extern Window window;
extern RendererManager RM;

extern bool displayInfo;

extern bool vsync;

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

extern int outlineType;

extern buttons_t press;
extern renderMode_t renderMode;


#endif