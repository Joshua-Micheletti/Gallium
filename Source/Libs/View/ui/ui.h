#include <string>
#include "imgui.h"
#include "../renderer/renderer.h"
#include "../../Controller/eventHandler.h"
#include "../../global.h"

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

		void drawImGui();

		void HelpMarker(const char*);
};
