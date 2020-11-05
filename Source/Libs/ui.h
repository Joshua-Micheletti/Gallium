#include <SFML/Graphics.hpp>
#include <string>

class UI {
	public:
		UI(sf::RenderWindow *);
		void updateDebugInfo();
		void updateFPS();
		void drawBoundingBoxText();
		void drawInfo();
		
	private:
		std::string floatToString(float, int);
		sf::RenderWindow *window;
		sf::Text debug;
		sf::Text fps;
		sf::Text frameTime;
		sf::Text boundingBoxText;
		sf::CircleShape crosshair;
		sf::Font font;
		sf::Clock fpsClock;
		sf::Time time;
		sf::Time tick;
		sf::Clock clock;
		sf::Time fpsTime;
};
