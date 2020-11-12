// standard libs
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <typeinfo>
#include <time.h>
#include <vector>

// APIs
#include <glad\glad.h>
#include <SFML\Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// external libs
#include "init.h"
#include "camera.h"
#include "entity.h"
#include "shader.h"
#include "renderer.h"
#include "ui.h"
#include "eventHandler.h"
