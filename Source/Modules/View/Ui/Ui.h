#include <stdlib.h>
#include <vector>
#include <string>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <algorithm>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "../../global.h"
#include "../../utils.h"

#include "../Renderer/Renderer.h"
#include "../../Controller/EventHandler.h"
#include "../../Model/Entity.h"

// needs to be after glad include from other headers
#include "GLFW/glfw3.h"


// class that shows onscreen informations
class UI {
	public:
		// constructor method which takes the window reference
		UI(Renderer *, EventHandler *);
		// method to draw the information on the screen
		void drawInfo();
		
	private:
		// m_renderer reference
		Renderer *m_renderer;
		// event handler reference
		EventHandler *m_eventHandler;

		// object to store frame time
		double m_fpsTime;

		float* m_color;

		char* m_windowTitle;

		bool m_showMetricsWindow;
		bool m_showUserGuide;
		bool m_showAboutWindow;
		bool m_showDemoWindow;
		bool m_showFPS;
		bool m_pauseFlag;
		bool m_showLeftColumn;
		bool m_showRightColumn;
		bool m_showBottomRow;

		ImVec2 m_menuBarSize;

		ImVec2 m_rightColumnSize;

		ImVec2 m_leftColumnSize;

		unsigned int m_depthTexture;

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
