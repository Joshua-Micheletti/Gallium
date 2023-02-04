#include <string>
#include <stdlib.h>

#include "glad/glad.h"
#define GLFW_DLL
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "utils.h"
#include "global.h"
#include "Timer.h"

#include "View/Renderer/Renderer.h"
#include "View/Model/Model.h"
#include "Controller/EventHandler.h"
#include "View/Ui/Ui.h"
#include "View/Window/Window.h"
#include "Sandbox/sandbox.h"