#ifndef __EVENTHANDLER__
#define __EVENTHANDLER__
#include <SFML\Graphics.hpp>
#include <glm\glm.hpp>

// class for handling keyboard, window and entity events
class EventHandler
{
	public:
		// constructor method (sets the reference to the window)
		EventHandler(sf::RenderWindow *);

		bool getUpdateFlag();
		void setUpdateFlag(bool);
		// calls all the event polling and management functions
		void routine();

	private:
		// reference to the window object
		sf::RenderWindow* window;
		// object for storing window events
		sf::Event windowEvent;
		
		// time variables for syncing event polling and update frequency to tickrate
		sf::Time time;
		sf::Time tick;
		sf::Clock clock;

		// tmp variables for updating entities
		float x1;
		float x2;
		float dist;
		float angle;

		bool update;

		
		// method for handling keyboard events
		void handleUserEvents();
		// method for handling window events
		void handleWindowEvents();
		// method for updating entities
		void updateEntities();
};
#endif
