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
		angle += 0.01f;

		// angle = 90.0f;

		glPointSize(100);

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

void createCube(std::vector<float>* array, std::vector<glm::vec3> faces) {
	array->push_back(faces[0].x);
	array->push_back(faces[0].y);
	array->push_back(faces[0].z);
	array->push_back(faces[1].x);
	array->push_back(faces[1].y);
	array->push_back(faces[1].z);

	array->push_back(faces[1].x);
	array->push_back(faces[1].y);
	array->push_back(faces[1].z);
	array->push_back(faces[2].x);
	array->push_back(faces[2].y);
	array->push_back(faces[2].z);

	array->push_back(faces[2].x);
	array->push_back(faces[2].y);
	array->push_back(faces[2].z);
	array->push_back(faces[3].x);
	array->push_back(faces[3].y);
	array->push_back(faces[3].z);

	array->push_back(faces[3].x);
	array->push_back(faces[3].y);
	array->push_back(faces[3].z);
	array->push_back(faces[0].x);
	array->push_back(faces[0].y);
	array->push_back(faces[0].z);

	array->push_back(faces[0].x);
	array->push_back(faces[0].y);
	array->push_back(faces[0].z);
	array->push_back(faces[5].x);
	array->push_back(faces[5].y);
	array->push_back(faces[5].z);

	array->push_back(faces[1].x);
	array->push_back(faces[1].y);
	array->push_back(faces[1].z);
	array->push_back(faces[6].x);
	array->push_back(faces[6].y);
	array->push_back(faces[6].z);

	array->push_back(faces[2].x);
	array->push_back(faces[2].y);
	array->push_back(faces[2].z);
	array->push_back(faces[7].x);
	array->push_back(faces[7].y);
	array->push_back(faces[7].z);

	array->push_back(faces[3].x);
	array->push_back(faces[3].y);
	array->push_back(faces[3].z);
	array->push_back(faces[4].x);
	array->push_back(faces[4].y);
	array->push_back(faces[4].z);

	array->push_back(faces[5].x);
	array->push_back(faces[5].y);
	array->push_back(faces[5].z);
	array->push_back(faces[4].x);
	array->push_back(faces[4].y);
	array->push_back(faces[4].z);

	array->push_back(faces[4].x);
	array->push_back(faces[4].y);
	array->push_back(faces[4].z);
	array->push_back(faces[7].x);
	array->push_back(faces[7].y);
	array->push_back(faces[7].z);

	array->push_back(faces[7].x);
	array->push_back(faces[7].y);
	array->push_back(faces[7].z);
	array->push_back(faces[6].x);
	array->push_back(faces[6].y);
	array->push_back(faces[6].z);

	array->push_back(faces[6].x);
	array->push_back(faces[6].y);
	array->push_back(faces[6].z);
	array->push_back(faces[5].x);
	array->push_back(faces[5].y);
	array->push_back(faces[5].z);
}

void createSphere(glm::vec3 center, float dist, int sides, std::vector<float>* data) {

	double pi = 3.1415926535897;

	glm::vec3 tmp;

	glm::vec3 tmp2;

	tmp = glm::vec3(dist, 0, 0) + center;

	for (float i = 0; i < 2 * pi; i += (2 * pi) / (float)sides) {
		tmp2.x = dist * cos(i);
		tmp2.y = dist * sin(i);
		tmp2.z = 0;

		data->push_back(tmp.x);
		data->push_back(tmp.y);
		data->push_back(tmp.z);

		tmp = tmp2 + center;

		data->push_back(tmp.x);
		data->push_back(tmp.y);
		data->push_back(tmp.z);
	}

	data->push_back(tmp.x);
	data->push_back(tmp.y);
	data->push_back(tmp.z);

	tmp = glm::vec3(dist, 0, 0) + center;

	data->push_back(tmp.x);
	data->push_back(tmp.y);
	data->push_back(tmp.z);



	tmp = glm::vec3(0, 0, dist) + center;

	for (float i = 0; i < 2 * pi; i += (2 * pi) / (float)sides) {
		tmp2.x = 0;
		tmp2.y = dist * sin(i);
		tmp2.z = dist * cos(i);

		data->push_back(tmp.x);
		data->push_back(tmp.y);
		data->push_back(tmp.z);

		tmp = tmp2 + center;

		data->push_back(tmp.x);
		data->push_back(tmp.y);
		data->push_back(tmp.z);
	}

	data->push_back(tmp.x);
	data->push_back(tmp.y);
	data->push_back(tmp.z);

	tmp = glm::vec3(0, 0, dist) + center;

	data->push_back(tmp.x);
	data->push_back(tmp.y);
	data->push_back(tmp.z);



	tmp = glm::vec3(0, 0, dist) + center;

	for (float i = 0; i < 2 * pi; i += (2 * pi) / (float)sides) {
		tmp2.x = dist * sin(i);
		tmp2.y = 0;
		tmp2.z = dist * cos(i);

		data->push_back(tmp.x);
		data->push_back(tmp.y);
		data->push_back(tmp.z);

		tmp = tmp2 + center;

		data->push_back(tmp.x);
		data->push_back(tmp.y);
		data->push_back(tmp.z);
	}

	data->push_back(tmp.x);
	data->push_back(tmp.y);
	data->push_back(tmp.z);

	tmp = glm::vec3(0, 0, dist) + center;

	data->push_back(tmp.x);
	data->push_back(tmp.y);
	data->push_back(tmp.z);
}

void drawBoundingBox(bounds_t bounds, unsigned int tmpBuffer, std::vector<Shader> shaderBuffer, glm::vec3 color) {
	std::vector<float> data;
	std::vector<glm::vec3> faces;
	faces.push_back(bounds.a);
	faces.push_back(bounds.b);
	faces.push_back(bounds.c);
	faces.push_back(bounds.d);
	faces.push_back(bounds.e);
	faces.push_back(bounds.f);
	faces.push_back(bounds.g);
	faces.push_back(bounds.h);
	createCube(&data, faces);

	glBindBuffer(GL_ARRAY_BUFFER, tmpBuffer);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

	glUseProgram(shaderBuffer[1].getID());

	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[0].id, 1, GL_FALSE, &(glm::mat4(1.0f)[0][0]));
	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[1].id, 1, GL_FALSE, &(camera.getViewMatrix()[0][0]));
	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[2].id, 1, GL_FALSE, &(Projection[0][0]));
	glUniform3f(shaderBuffer[1].getUniformBuffer()[3].id, color.x, color.y, color.z);

	glEnableVertexAttribArray(0);
	// glBindBuffer(GL_ARRAY_BUFFER, tmpBuffer2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_LINES, 0, data.size());

	glDisableVertexAttribArray(0);
}

void drawBoundingSphere(float radius, glm::vec3 center, unsigned int tmpBuffer, std::vector<Shader> shaderBuffer, glm::vec3 color) {
	std::vector<float> data;

	createSphere(center, radius, 30, &data);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

	glUseProgram(shaderBuffer[1].getID());

	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[0].id, 1, GL_FALSE, &(glm::mat4(1.0f)[0][0]));
	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[1].id, 1, GL_FALSE, &(camera.getViewMatrix()[0][0]));
	glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[2].id, 1, GL_FALSE, &(Projection[0][0]));
	glUniform3f(shaderBuffer[1].getUniformBuffer()[3].id, color.x, color.y, color.z);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_LINES, 0, data.size());

	glDisableVertexAttribArray(0);
}

void displayBoundingBox(sf::RenderWindow* window, sf::Text* bb, std::vector<Entity*> entityBuffer, std::vector<Shader> shaderBuffer, unsigned int tmpBuffer) {

	sf::FloatRect bbBounds;

	for (int i = 0; i < entityBuffer.size(); i++) {
		if (drawOBB) {
			drawBoundingBox(entityBuffer[i]->getObjectBoundingBox(true), tmpBuffer, shaderBuffer, glm::vec3(1, 0, 0));
			window->pushGLStates();
			bb->setString("Object Bounding Box");
			bbBounds = bb->getLocalBounds();
			bb->setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
			bb->setFillColor(sf::Color(255, 0, 0));
			bb->setPosition((window->getSize().x / 8) * 1 - (window->getSize().x / 8) / 2, window->getSize().y - 20);
			window->draw(*bb);
			window->popGLStates();
		}

		if (drawAABB1) {
			drawBoundingBox(entityBuffer[i]->getExternalAxisAlignedBoundingBox(true), tmpBuffer, shaderBuffer, glm::vec3(0, 1, 0));
			window->pushGLStates();
			bb->setString("External Axis Aligned Bounding Box");
			bbBounds = bb->getLocalBounds();
			bb->setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
			bb->setFillColor(sf::Color(0, 255, 0));
			bb->setPosition((window->getSize().x / 8) * 2 - (window->getSize().x / 8) / 2, window->getSize().y - 20);
			window->draw(*bb);
			window->popGLStates();
		}

		if (drawAABB2) {
			drawBoundingBox(entityBuffer[i]->getInternalAxisAlignedBoundingBox(true), tmpBuffer, shaderBuffer, glm::vec3(0, 0, 1));
			window->pushGLStates();
			bb->setString("Internal AABB");
			bbBounds = bb->getLocalBounds();
			bb->setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
			bb->setFillColor(sf::Color(0, 0, 255));
			bb->setPosition((window->getSize().x / 8) * 3 - (window->getSize().x / 8) / 2, window->getSize().y - 20);
			window->draw(*bb);
			window->popGLStates();
		}

		if (drawAABB3) {
			bounds_t internalWorldBounds;
			internalWorldBounds = entityBuffer[i]->getInternalAxisAlignedBoundingBox(true);

			bounds_t worldBounds;
			worldBounds = entityBuffer[i]->getExternalAxisAlignedBoundingBox(true);

			std::vector<float> data5;

			glm::vec3 a2 = glm::vec3((worldBounds.a.x + internalWorldBounds.a.x) / 2, (worldBounds.a.y + internalWorldBounds.a.y) / 2, (worldBounds.a.z + internalWorldBounds.a.z) / 2);
			glm::vec3 b2 = glm::vec3((worldBounds.b.x + internalWorldBounds.b.x) / 2, (worldBounds.b.y + internalWorldBounds.b.y) / 2, (worldBounds.b.z + internalWorldBounds.b.z) / 2);
			glm::vec3 c2 = glm::vec3((worldBounds.c.x + internalWorldBounds.c.x) / 2, (worldBounds.c.y + internalWorldBounds.c.y) / 2, (worldBounds.c.z + internalWorldBounds.c.z) / 2);
			glm::vec3 d2 = glm::vec3((worldBounds.d.x + internalWorldBounds.d.x) / 2, (worldBounds.d.y + internalWorldBounds.d.y) / 2, (worldBounds.d.z + internalWorldBounds.d.z) / 2);
			glm::vec3 e2 = glm::vec3((worldBounds.e.x + internalWorldBounds.e.x) / 2, (worldBounds.e.y + internalWorldBounds.e.y) / 2, (worldBounds.e.z + internalWorldBounds.e.z) / 2);
			glm::vec3 f2 = glm::vec3((worldBounds.f.x + internalWorldBounds.f.x) / 2, (worldBounds.f.y + internalWorldBounds.f.y) / 2, (worldBounds.f.z + internalWorldBounds.f.z) / 2);
			glm::vec3 g2 = glm::vec3((worldBounds.g.x + internalWorldBounds.g.x) / 2, (worldBounds.g.y + internalWorldBounds.g.y) / 2, (worldBounds.g.z + internalWorldBounds.g.z) / 2);
			glm::vec3 h2 = glm::vec3((worldBounds.h.x + internalWorldBounds.h.x) / 2, (worldBounds.h.y + internalWorldBounds.h.y) / 2, (worldBounds.h.z + internalWorldBounds.h.z) / 2);

			std::vector<glm::vec3> faces4;
			faces4.push_back(a2);
			faces4.push_back(b2);
			faces4.push_back(c2);
			faces4.push_back(d2);
			faces4.push_back(e2);
			faces4.push_back(f2);
			faces4.push_back(g2);
			faces4.push_back(h2);
			createCube(&data5, faces4);

			glBufferData(GL_ARRAY_BUFFER, data5.size() * sizeof(float), &data5[0], GL_STATIC_DRAW);

			glUseProgram(shaderBuffer[1].getID());

			glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[0].id, 1, GL_FALSE, &(glm::mat4(1.0f)[0][0]));
			glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[1].id, 1, GL_FALSE, &(camera.getViewMatrix()[0][0]));
			glUniformMatrix4fv(shaderBuffer[1].getUniformBuffer()[2].id, 1, GL_FALSE, &(Projection[0][0]));
			glUniform3f(shaderBuffer[1].getUniformBuffer()[3].id, 0, 1, 1);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glPointSize(10.0f);

			glDrawArrays(GL_LINES, 0, data5.size());

			glDisableVertexAttribArray(0);

			window->pushGLStates();
			bb->setString("Average AABB");
			bbBounds = bb->getLocalBounds();
			bb->setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
			bb->setFillColor(sf::Color(0, 255, 255));
			bb->setPosition((window->getSize().x / 8) * 4 - (window->getSize().x / 8) / 2, window->getSize().y - 20);
			window->draw(*bb);
			window->popGLStates();
		}

		if (drawAABB4) {
			drawBoundingBox(entityBuffer[i]->getAxisAlignedBoundingBox(true), tmpBuffer, shaderBuffer, glm::vec3(1, 0, 1));
			window->pushGLStates();
			bb->setString("True AABB");
			bbBounds = bb->getLocalBounds();
			bb->setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
			bb->setFillColor(sf::Color(255, 0, 255));
			bb->setPosition((window->getSize().x / 8) * 5 - (window->getSize().x / 8) / 2, window->getSize().y - 20);
			window->draw(*bb);
			window->popGLStates();
		}

		if (drawBS) {
			drawBoundingSphere(entityBuffer[i]->getInternalBoundingSphere(false), entityBuffer[i]->getWorldPosition(), tmpBuffer, shaderBuffer, glm::vec3(1, 1, 0));
			window->pushGLStates();
			bb->setString("Internal Bounding Sphere");
			bbBounds = bb->getLocalBounds();
			bb->setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
			bb->setFillColor(sf::Color(255, 255, 0));
			bb->setPosition((window->getSize().x / 8) * 6 - (window->getSize().x / 8) / 2, window->getSize().y - 20);
			window->draw(*bb);
			window->popGLStates();
		}

		if (drawBS2) {
			drawBoundingSphere(entityBuffer[i]->getExternalBoundingSphere(false), entityBuffer[i]->getWorldPosition(), tmpBuffer, shaderBuffer, glm::vec3(1, 0.5, 0));
			window->pushGLStates();
			bb->setString("External Bounding Sphere");
			bbBounds = bb->getLocalBounds();
			bb->setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
			bb->setFillColor(sf::Color(255, 127, 0));
			bb->setPosition((window->getSize().x / 8) * 7 - (window->getSize().x / 8) / 2, window->getSize().y - 20);
			window->draw(*bb);
			window->popGLStates();
		}

		if (drawBS3) {
			drawBoundingSphere(entityBuffer[i]->getBoundingSphere(false), entityBuffer[i]->getWorldPosition(), tmpBuffer, shaderBuffer, glm::vec3(0.5, 1, 0));
			window->pushGLStates();
			bb->setString("True Bounding Sphere");
			bbBounds = bb->getLocalBounds();
			bb->setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
			bb->setFillColor(sf::Color(127, 255, 0));
			bb->setPosition((window->getSize().x / 8) * 8 - (window->getSize().x / 8) / 2, window->getSize().y - 20);
			window->draw(*bb);
			window->popGLStates();
		}
	}
}


/*  ___________________________________________________________________________________________________________________________________________________________________________ */
/* |                                                                          MAIN                                                                                            | */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾  */

int main(void) {
	sf::RenderWindow* window = setup();
	UI interface(window);

	sf::Clock clock;
	sf::Time time;
	sf::Time tick = sf::milliseconds(1000 / 300);
	time = clock.getElapsedTime();

	camera.mainCamera = true;

	// SFML elements initialization

	sf::Mouse::setPosition(center);

	setupRender();

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

		/* OpenGL */
		/* ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */

		render();

		// displayBoundingBox(window, &bb, entityBuffer, shaderBuffer, tmpBuffer);
		drawBoundingSphere(0, glm::vec3(0, 0, 0), tmpBuffer, shaderBuffer, glm::vec3(1, 1, 1));

		/* SFML */
		/* ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */
		window->pushGLStates();
		window->resetGLStates();

		if (displayInfo) {
			interface.drawDebugInfo();
			interface.drawFPS();
			//displayFPS(window, &fps, &fpsClock);
		}

		interface.drawCrosshair();
		window->popGLStates();

		window->display();	
	}

	return(0);
}
