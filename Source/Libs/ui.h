#include <SFML/Graphics.hpp>
#include <string>
#include "imgui.h"
//#include "imgui-SFML.h"
#include "renderer.h"
#include "eventHandler.h"

// class that shows onscreen informations
class UI {
	public:
		// constructor method which takes the window reference
		UI(GLFWwindow *, Renderer *, EventHandler *);
		// method to draw the information on the screen
		void drawInfo();

		void setReferenceWindow(GLFWwindow*);
		
	private:
		// window reference
		GLFWwindow* window;
		// renderer reference
		Renderer *renderer;
		// event handler reference
		EventHandler *eventHandler;

		// clock for keeping time of frame time
		sf::Clock fpsClock;
		// object to store frame time
		sf::Time fpsTime;
		// object to store elapsed time, used for defining the UI update rate
		sf::Time time;
		// delay between UI updates
		sf::Time tick;
		// clock to measure update time for the UI
		sf::Clock clock;

		sf::Clock deltaClock;

		sf::Color bgColor;

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
