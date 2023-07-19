#include "global.h"

Timer setupTimer;

Window window = Window();
RendererManager RM;
PhysicsWorld PW;
Engine engine;

bool displayInfo = true;
bool vsync = true;

bool freeMouse = false;
bool drawOBB = false;
bool drawAABB1 = false;
bool drawAABB2 = false;
bool drawAABB3 = false;
bool drawAABB4 = false;
bool drawBS = false;
bool drawBS2 = false;
bool drawBS3 = false;
bool doReflection = false;
int outlineType = 0;

unsigned int screenWidth = 1280;
unsigned int screenHeight = 720;
unsigned int windowWidth = 1280;
unsigned int windowHeight = 720;

buttons_t press;
renderMode_t renderMode;

