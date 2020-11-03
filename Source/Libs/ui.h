#include <SFML/Graphics.hpp>

class UI {
	public:
		UI(sf::RenderWindow *);
		void drawDebugInfo();
		void drawCrosshair();
		void drawFPS();
		
	private:
		sf::RenderWindow *window;
		sf::Text debug;
		sf::Text fps;
		sf::Text bb;
		sf::CircleShape crosshair;
		sf::Font arial;
		sf::Clock fpsClock;
};
