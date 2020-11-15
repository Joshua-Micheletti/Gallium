#ifndef __EVENTHANDLER__
#define __EVENTHANDLER__
#include <SFML\Graphics.hpp>
#include "GLFW/glfw3.h"
#include <glm\glm.hpp>
#include "init.h"

// class for handling keyboard, window and entity events
class EventHandler
{
	public:
		// constructor method (sets the reference to the window)
		EventHandler(GLFWwindow *);

		bool getUpdateFlag();
		void setUpdateFlag(bool);
		// calls all the event polling and management functions
		void routine();
		void setWindowVSync();
		void setWindowReference(GLFWwindow*);

	private:
		void handleUserEvents();
		// reference to the window object
		GLFWwindow* window;
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
		//void handleUserEvents();
		// method for handling window events
		void handleWindowEvents();
		// method for updating entities
		void updateEntities();
};
#endif
