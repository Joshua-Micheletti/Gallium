#include "Libs/lib.h"

float x1 = 1;
float x2 = 1;

float dist = 100.0f;
float angle = 0.0f;

glm::vec3 lightPos = glm::vec3(60.0, 10.0, 60.0);

void updateEntity(Entity* entity) {
	if (entity->getName().compare("walnut") == 0) {
		// entity->move(glm::vec3(0.005f, 0.005f, 0.005f), camera.getViewMatrix());
		//
		// entity->rotate(-0.1f, 0.2f, 0.3f);
		//
		// entity->scale(1.0001f);
	}

	else if (entity->getName().compare("box") == 0) {
		// entity->rotate(0.1f, 0.1f, 0.1f);

		// entity->scale(1 - 0.01f);
	}

	else if (entity->getName().compare("monkey") == 0) {
		x2 = x1;
		x1 += 0.01;
		entity->scale(1 / (sin(x2) + 2.0f));
		entity->scale(sin(x1) + 2.0f);

		entity->rotate(0.1f, 0.1f, -0.1f);
	}

	else if (entity->getName().compare("man") == 0) {
		// entity->rotate(0.3f, 0.2f, 0.1f);
		// entity->move(glm::vec3(-0.01f, -0.01f, -0.01f), camera.getViewMatrix());
	}

	else if (entity->getName().compare("light") == 0) {
		angle += 0.001f;

		// angle = 90.0f;

		glPointSize(30);

		lightPos.x = dist * cos(angle);
		lightPos.z = dist * sin(angle);
		// lightPos.y += 0.1;

		light->placeAt(glm::vec3(lightPos.x, lightPos.y, lightPos.z), camera.getViewMatrix());
		// light->placeAt(camera.getPosition(), camera.getViewMatrix());
	}

	else if (entity->getName().compare("man2") == 0) {
		entity->rotate(0.0f, 0.2f, 0.0f);
	}

	else if (entity->getName().compare("man3") == 0) {
		entity->rotate(0.0f, 0.2f, 0.0f);
	}
}

void handleEvents(sf::RenderWindow* window) {
	float cameraSpeed = 0.02f;
	float sensitivity = 0.08f;

	// camera moovement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		cameraSpeed *= 3;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			camera.setPosition(camera.getPosition() - glm::normalize(glm::cross(camera.getOrientationCartesian(), camera.getUp())) * cameraSpeed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			camera.setPosition(camera.getPosition() + glm::normalize(glm::cross(camera.getOrientationCartesian(), camera.getUp())) * cameraSpeed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			camera.setPosition(camera.getPosition() + camera.getOrientationCartesian() * cameraSpeed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			camera.setPosition(camera.getPosition() - camera.getOrientationCartesian() * cameraSpeed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			camera.setPosition(camera.getPosition() + camera.getUp() * cameraSpeed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
			camera.setPosition(camera.getPosition() - camera.getUp() * cameraSpeed);
		}
	}

	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			camera.setPosition(camera.getPosition() - glm::normalize(glm::cross(camera.getOrientationCartesian(), camera.getUp())) * cameraSpeed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			camera.setPosition(camera.getPosition() + glm::normalize(glm::cross(camera.getOrientationCartesian(), camera.getUp())) * cameraSpeed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			camera.setPosition(camera.getPosition() + camera.getOrientationCartesian() * cameraSpeed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			camera.setPosition(camera.getPosition() - camera.getOrientationCartesian() * cameraSpeed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			camera.setPosition(camera.getPosition() + camera.getUp() * cameraSpeed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
			camera.setPosition(camera.getPosition() - camera.getUp() * cameraSpeed);
		}
	}

	// look movement
	if (freeMouse == false) {
		float offX = sf::Mouse::getPosition().x - center.x;
		float offY = center.y - sf::Mouse::getPosition().y;

		camera.setOrientation(glm::vec3(camera.getOrientation().x, camera.getOrientation().y + offX * sensitivity, camera.getOrientation().z + offY * sensitivity));

		sf::Mouse::setPosition(center);

		window->setMouseCursorVisible(false);
	}
	else {
		window->setMouseCursorVisible(true);
	}


	// shortcuts:

	// "\" toggle debug info
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backslash) && !press.backslash) {
		press.backslash = true;

		if (displayInfo == true) {
			displayInfo = false;
		}
		else {
			displayInfo = true;
		}
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Backslash)) {
		press.backslash = false;
	}

	// "L" toggle wireframe
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && !press.L) {
		press.L = true;

		if (renderMode == wireframe) {
			renderMode = base;
		}
		else {
			renderMode = wireframe;
		}
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
		press.L = false;
	}

	// "P" toggle points
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && !press.P) {
		press.P = true;

		if (renderMode == vertices) {
			renderMode = base;
		}
		else {
			renderMode = vertices;
		}
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		press.P = false;
	}

	// "Z" toggle OBB
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !press.Z) {
		press.Z = true;

		if (drawOBB == true) {
			drawOBB = false;
		}
		else {
			drawOBB = true;
		}
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		press.Z = false;
	}

	// "X" toggle AABB (small)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !press.X) {
		press.X = true;

		if (drawAABB1 == true) {
			drawAABB1 = false;
		}
		else {
			drawAABB1 = true;
		}
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
		press.X = false;
	}

	// "C" toggle AABB (large)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && !press.C) {
		press.C = true;

		if (drawAABB2 == true) {
			drawAABB2 = false;
		}
		else {
			drawAABB2 = true;
		}
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		press.C = false;
	}

	// "V" toggle AABB (average)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) && !press.V) {
		press.V = true;

		if (drawAABB3 == true) {
			drawAABB3 = false;
		}
		else {
			drawAABB3 = true;
		}
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
		press.V = false;
	}

	// "B" toggle AABB (exact)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && !press.B) {
		press.B = true;

		if (drawAABB4 == true) {
			drawAABB4 = false;
		}
		else {
			drawAABB4 = true;
		}
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
		press.B = false;
	}

	// "N" toggle bounding sphere (small)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && !press.N) {
		press.N = true;

		if (drawBS == true) {
			drawBS = false;
		}
		else {
			drawBS = true;
		}
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
		press.N = false;
	}

	// "M" toggle bounding sphere (large)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && !press.M) {
		press.M = true;

		if (drawBS2 == true) {
			drawBS2 = false;
		}
		else {
			drawBS2 = true;
		}
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
		press.M = false;
	}

	// "K" toggle bounding sphere (average)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && !press.K) {
		press.K = true;

		if (drawBS3 == true) {
			drawBS3 = false;
		}
		else {
			drawBS3 = true;
		}
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		press.K = false;
	}

	// "LAlt" toggle free mouse
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && !press.LAlt) {
		press.LAlt = true;

		if (freeMouse == true) {
			freeMouse = false;
		}
		else {
			freeMouse = true;
		}
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
		press.LAlt = false;
	}
}


/*  ___________________________________________________________________________________________________________________________________________________________________________ */
/* |                                                                          MAIN                                                                                            | */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾  */

int main(void) {
	sf::RenderWindow* window = setup();
	Renderer renderer;
	UI interface(window);

	sf::Clock clock;
	sf::Time time;
	sf::Time tick = sf::milliseconds(1000 / 300);
	time = clock.getElapsedTime();

	camera.mainCamera = true;

	sf::Mouse::setPosition(center);

	/*  ___________________________________________________________________________________________________________________________________________________________________________ */
	/* |                                                                          LOOP                                                                                            | */
	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾  */

	while (window->isOpen()) {
		/* Event Handling */
		/* ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */
		sf::Event event;

		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
		}

		while (time.asMilliseconds() + tick.asMilliseconds() < clock.getElapsedTime().asMilliseconds()) {
			handleEvents(window);

			for (int i = 0; i < entityBuffer.size(); i++) {
				updateEntity(entityBuffer[i]);
			}

			time += tick;
		}

		renderer.render();

		interface.drawInfo();

		window->display();	
	}

	return(0);
}
