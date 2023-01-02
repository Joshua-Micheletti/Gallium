#include "EventHandler.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_W) {
		if (action == GLFW_PRESS) {
			press.W = true;
		}
		else if (action == GLFW_RELEASE) {
			press.W = false;
		}
	}

	if (key == GLFW_KEY_A) {
		if (action == GLFW_PRESS) {
			press.A = true;
		}
		else if (action == GLFW_RELEASE) {
			press.A = false;
		}
	}

	if (key == GLFW_KEY_S) {
		if (action == GLFW_PRESS) {
			press.S = true;
		}
		else if (action == GLFW_RELEASE) {
			press.S = false;
		}
	}

	if (key == GLFW_KEY_D) {
		if (action == GLFW_PRESS) {
			press.D = true;
		}
		else if (action == GLFW_RELEASE) {
			press.D = false;
		}
	}

	if (key == GLFW_KEY_LEFT_SHIFT) {
		if (action == GLFW_PRESS) {
			press.LSHIFT = true;
		}
		else if (action == GLFW_RELEASE) {
			press.LSHIFT = false;
		}
	}

	if (key == GLFW_KEY_SPACE) {
		if (action == GLFW_PRESS) {
			press.SPACE = true;
		}
		else if (action == GLFW_RELEASE) {
			press.SPACE = false;
		}
	}

	if (key == GLFW_KEY_LEFT_CONTROL) {
		if (action == GLFW_PRESS) {
			press.LCTRL = true;
		}
		else if (action == GLFW_RELEASE) {
			press.LCTRL = false;
		}
	}

	if (key == 96 && action == GLFW_PRESS && press.backslash == false) {
		press.backslash = true;

		if (displayInfo == true) {
			displayInfo = false;
		}
		else {
			displayInfo = true;
		}
	}
	else if (key == 96 && action == GLFW_RELEASE) {
		press.backslash = false;
	}

	if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS && press.LALT == false) {
		press.LALT = true;

		if (freeMouse == true) {
			freeMouse = false;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else {
			freeMouse = true;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
	else if (key == GLFW_KEY_LEFT_ALT && action == GLFW_RELEASE) {
		press.LALT = false;
	}
}

EventHandler::EventHandler(GLFWwindow* window) {
	this->window = window;
	this->update = true;
	this->time = glfwGetTime();
	this->tick = (double)(1.0 / 300.0);

	glfwSetKeyCallback(this->window, keyCallback);

	x1 = 1;
	x2 = 1;

	dist = 100.0f;
	angle = 0.0f;
}

void EventHandler::updateEntities() {
	// TO BE CHANGED, SHOULD WORK ON ENTITIES, NOT DRAWING ENTITIES
	float r = 50.0f;

	static float teta = 0.0f; 

	teta += 0.001;

	float x;
	float y;

	polarToCartesian(r, teta, &x, &y);

	RM.model("M_Light")->position(glm::vec3(x, 10.0f, y));
}

void EventHandler::handleUserEvents() {
	float cameraSpeed = 0.02f;
	float sensitivity = 0.08f;

	// look movement
	if (freeMouse == false) {
		double xpos;
		double ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		float offX = xpos - (screenWidth / 2);
		float offY = (screenHeight / 2) - ypos;

		RM.camera()->orientation(glm::vec3(RM.camera()->orientation().x, RM.camera()->orientation().y + offX * sensitivity, RM.camera()->orientation().z + offY * sensitivity));
		

		/*sf::Mouse::setPosition(center);*/
		glfwSetCursorPos(this->window, screenWidth / 2, screenHeight / 2);

		//window->setMouseCursorVisible(false);
	}

	if (press.LSHIFT == true) {
		cameraSpeed *= 3;
	}

	if (press.W == true) {
		RM.camera()->position(RM.camera()->position() + RM.camera()->orientationCartesian() * cameraSpeed);
	}

	if (press.S == true) {
		RM.camera()->position(RM.camera()->position() - RM.camera()->orientationCartesian() * cameraSpeed);
	}

	if (press.A == true) {
		RM.camera()->position(RM.camera()->position() - glm::normalize(glm::cross(RM.camera()->orientationCartesian(), RM.camera()->up())) * cameraSpeed);
	}
			
	if (press.D == true) {
		RM.camera()->position(RM.camera()->position() + glm::normalize(glm::cross(RM.camera()->orientationCartesian(), RM.camera()->up())) * cameraSpeed);
	}

	if (press.SPACE == true) {
		RM.camera()->position(RM.camera()->position() + RM.camera()->up() * cameraSpeed);
	}
		
	if (press.LCTRL == true) {
		RM.camera()->position(RM.camera()->position() - RM.camera()->up() * cameraSpeed);
	}
}

void EventHandler::routine() {
	while (this->time + this->tick < glfwGetTime()) {
		handleUserEvents();

		if (this->update == true) {
			updateEntities();
		}

		this->time += this->tick;
	}
}

void EventHandler::setUpdateFlag(bool value) {
	this->update = value;
}

bool EventHandler::getUpdateFlag() {
	return(this->update);
}

void EventHandler::setWindowReference(GLFWwindow* window) {
	this->window = window;
}