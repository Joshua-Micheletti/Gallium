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
		// text containing entity information
		sf::Text debug;
		// text containing fps (frame/s)
		sf::Text fps;
		// text containing frame time (ms)
		sf::Text frameTime;
		// text containing names of displayed bounding boxes
		sf::Text boundingBoxText;
		// crosshair
		sf::CircleShape crosshair;
		// font for on-screen text
		sf::Font font;
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

		ImVec2 menuBarSize;

		// fetch data from entities, format it and save it into this->debug
		void updateDebugInfo();
		// pass the elapsed time to the fps text
		void updateFPS();
		// check the displayed bounding boxes and shows the corresponding texts through boundingBoxText
		void drawBoundingBoxText();

		void setupImGuiStyle();

		void drawMenuBar();

		void drawFPSWindow();

		void drawLeftColumn();

		void drawImGui();
		// method to turn a float into a string with a desired decimal precision
		std::string floatToString(float, int);
};
