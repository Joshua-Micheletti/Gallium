#include <SFML\Graphics.hpp>
#include <glm\glm.hpp>

class EventHandler
{
	public:
		EventHandler(sf::RenderWindow *);
		void routine();

	private:
		void handleUserEvents();
		void handleWindowEvents();
		void updateEntities();

		sf::RenderWindow* window;
		sf::Event windowEvent;
		float x1;
		float x2;
		float dist;
		float angle;
		glm::vec3 lightPos;
		sf::Time time;
		sf::Time tick;
		sf::Clock clock;
};

