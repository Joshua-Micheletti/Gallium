#include "eventHandler.h"
#include "../init.h"
#include "../View/camera.h"
#include "../Model/entity.h"
#include <glm/glm.hpp>
#include "GLFW/glfw3.h"

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

	RM.drawingEntity("DE_Light")->position(glm::vec3(x, 10.0f, y));


	// for (int i = 0; i < entityBuffer.size(); i++) {
	// 	Entity* entity = entityBuffer[i];

	// 	if (entity->getName().compare("walnut") == 0) {
	// 		// entity->move(glm::vec3(0.005f, 0.005f, 0.005f), camera.getViewMatrix());
	// 		//
	// 		// entity->rotate(-0.1f, 0.2f, 0.3f);
	// 		//
	// 		// entity->scale(1.0001f);
	// 	}

	// 	else if (entity->getName().compare("box") == 0) {
	// 		// entity->rotate(0.1f, 0.1f, 0.1f);

	// 		// entity->scale(1 - 0.01f);
	// 	}

	// 	else if (entity->getName().compare("monkey") == 0) {
	// 		x2 = x1;
	// 		x1 += 0.01;
	// 		entity->scale(1 / (sin(x2) + 2.0f));
	// 		entity->scale(sin(x1) + 2.0f);

	// 		entity->rotate(0.1f, 0.1f, -0.1f);
	// 	}

	// 	else if (entity->getName().compare("man") == 0) {
	// 		// entity->rotate(0.3f, 0.2f, 0.1f);
	// 		// entity->move(glm::vec3(-0.01f, -0.01f, -0.01f), camera.getViewMatrix());
	// 	}

	// 	else if (entity->getName().compare("light") == 0) {
	// 		angle += 0.001f;

	// 		glPointSize(30);

	// 		light->placeAt(glm::vec3(dist * cos(angle), 10.0, dist * sin(angle)), camera.getViewMatrix());
	// 	}

	// 	else if (entity->getName().compare("man2") == 0) {
	// 		entity->rotate(0.0f, 0.2f, 0.0f);
	// 	}

	// 	else if (entity->getName().compare("man3") == 0) {
	// 		entity->rotate(0.0f, 0.2f, 0.0f);
	// 	}

	// 	else if (entity->getName().compare("manaya") == 0) {
	// 		entity->rotate(0.1f, 0.0f, 0.0f);
	// 	}
	// }
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

		RM.camera()->setOrientation(glm::vec3(RM.camera()->getOrientation().x, RM.camera()->getOrientation().y + offX * sensitivity, RM.camera()->getOrientation().z + offY * sensitivity));
		

		/*sf::Mouse::setPosition(center);*/
		glfwSetCursorPos(this->window, screenWidth / 2, screenHeight / 2);

		//window->setMouseCursorVisible(false);
	}

	if (press.LSHIFT == true) {
		cameraSpeed *= 3;
	}

	if (press.W == true) {
		RM.camera()->setPosition(RM.camera()->getPosition() + RM.camera()->getOrientationCartesian() * cameraSpeed);
	}

	if (press.S == true) {
		RM.camera()->setPosition(RM.camera()->getPosition() - RM.camera()->getOrientationCartesian() * cameraSpeed);
	}

	if (press.A == true) {
		RM.camera()->setPosition(RM.camera()->getPosition() - glm::normalize(glm::cross(RM.camera()->getOrientationCartesian(), RM.camera()->getUp())) * cameraSpeed);
	}
			
	if (press.D == true) {
		RM.camera()->setPosition(RM.camera()->getPosition() + glm::normalize(glm::cross(RM.camera()->getOrientationCartesian(), RM.camera()->getUp())) * cameraSpeed);
	}

	if (press.SPACE == true) {
		RM.camera()->setPosition(RM.camera()->getPosition() + RM.camera()->getUp() * cameraSpeed);
	}
		
	if (press.LCTRL == true) {
		RM.camera()->setPosition(RM.camera()->getPosition() - RM.camera()->getUp() * cameraSpeed);
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