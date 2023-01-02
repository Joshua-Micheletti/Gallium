#ifndef __EVENTHANDLER__
#define __EVENTHANDLER__

#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>

#include "../global.h"

#include "../View/Camera/Camera.h"
#include "../Model/Entity.h"

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
		
		// time variables for syncing event polling and update frequency to tickrate
		double time;
		double tick;

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
