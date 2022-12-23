#include "../../global.h"
// #include "../../init.h"
#include "../../Model/entity.h"
#include "../../utils.h"
#include <stdlib.h>
#include <vector>
#include <string>
#include <math.h>
#include <sstream>
#include <iomanip>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "../renderer/renderer.h"
#include "../../Controller/eventHandler.h"
#include "GLFW/glfw3.h"
#include <stdio.h>
#include <algorithm>
#include <stdio.h>
#include <iostream>

// class that shows onscreen informations
class UI {
	public:
		// constructor method which takes the window reference
		UI(Renderer *, EventHandler *);
		// method to draw the information on the screen
		void drawInfo();
		
	private:
		// renderer reference
		Renderer *renderer;
		// event handler reference
		EventHandler *eventHandler;

		// object to store frame time
		double fpsTime;

		float* color;

		char* windowTitle;

		bool showMetricsWindow;
		bool showUserGuide;
		bool showAboutWindow;
		bool showDemoWindow;
		bool showFPS;
		bool pauseFlag;
		bool showLeftColumn;
		bool showRightColumn;
		bool showBottomRow;

		ImVec2 menuBarSize;

		ImVec2 rightColumnSize;

		ImVec2 leftColumnSize;

		unsigned int depthTexture;

		void setupImGuiStyle();

		void drawImage(unsigned int, float, float);

		void drawMenuBar();

		void drawFPSWindow();

		void drawLeftColumn();

		void drawRightColumn();

		void drawBottomRow();

		void drawCrosshair();

		void drawImGui();

		void HelpMarker(const char*);
};
