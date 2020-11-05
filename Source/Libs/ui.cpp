#include "ui.h"
#include "init.h"
#include "entity.h"
#include <stdlib.h>
#include <vector>
#include <string>
#include <math.h>
#include <sstream>
#include <iomanip>

UI::UI(sf::RenderWindow *window) {
	UI::window = window;
	tick = sf::milliseconds(1000 / 10);
	time = clock.getElapsedTime();

	if (!font.loadFromFile("../Fonts/segmono_boot.ttf")) {
		printf("COULDN'T LOAD FONT\n");
	}

	boundingBoxText.setFont(font);
	debug.setFont(font);
	fps.setFont(font);
	frameTime.setFont(font);

	debug.setCharacterSize(16);
	debug.setFillColor(sf::Color::White);
	debug.setPosition(5, 5);
	debug.setOutlineThickness(1);
	debug.setOutlineColor(sf::Color::Black);

	fps.setCharacterSize(16);
	fps.setFillColor(sf::Color::White);
	fps.setOutlineThickness(1);
	fps.setOutlineColor(sf::Color::Black);

	frameTime.setCharacterSize(16);
	frameTime.setFillColor(sf::Color::White);
	frameTime.setOutlineThickness(1);
	frameTime.setOutlineColor(sf::Color::Black);

	boundingBoxText.setCharacterSize(16);
	boundingBoxText.setFillColor(sf::Color::Red);
	boundingBoxText.setOutlineThickness(1);
	boundingBoxText.setOutlineColor(sf::Color::Black);

	crosshair.setRadius(2);
	crosshair.setFillColor(sf::Color(255, 255, 255));
	sf::FloatRect crosshairBounds = crosshair.getLocalBounds();
	crosshair.setOrigin(crosshairBounds.left + crosshairBounds.width / 2, crosshairBounds.top + crosshairBounds.height / 2);
	crosshair.setPosition(screenWidth / 2, screenHeight / 2);
	crosshair.setOutlineThickness(1);
	crosshair.setOutlineColor(sf::Color::Black);
}

void UI::updateDebugInfo() {
	std::string text;
	for (int i = 0; i < entityBuffer.size(); i++) {
		text.append("> " +
			std::string(entityBuffer[i]->getName()) + ":\n  Position: (" +
			floatToString(entityBuffer[i]->getWorldPosition().x, 2) + ", " +
			floatToString(entityBuffer[i]->getWorldPosition().y, 2) + ", " +
			floatToString(entityBuffer[i]->getWorldPosition().z, 2) + ")\n  Rotation: (" +
			floatToString(entityBuffer[i]->getRotationFactor().x, 2) + ", " +
			floatToString(entityBuffer[i]->getRotationFactor().y, 2) + ", " +
			floatToString(entityBuffer[i]->getRotationFactor().z, 2) + ")\n  Scale: " +
			floatToString(entityBuffer[i]->getScalingFactor(), 2) + "\n\n");
	}
	debug.setString(text);
}

std::string UI::floatToString(float number, int precision) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(precision) << number;
	std::string s = stream.str();
	return(s);
}

void UI::updateFPS() {
	fps.setString(floatToString(1000.0f / fpsTime.asMilliseconds(), 0));
	frameTime.setString(floatToString(fpsTime.asMicroseconds() / 1000.0f, 2));

	sf::FloatRect fpsBounds = fps.getLocalBounds();
	fps.setOrigin(fpsBounds.left + fpsBounds.width, fpsBounds.top);
	fps.setPosition(window->getSize().x - 5, 5);

	fpsBounds = frameTime.getLocalBounds();
	frameTime.setOrigin(fpsBounds.left + fpsBounds.width, fpsBounds.top);
	frameTime.setPosition(window->getSize().x - 5, 20);
}

void UI::drawBoundingBoxText() {
	sf::FloatRect bbBounds;

	if (drawOBB) {
		boundingBoxText.setString("Object Bounding Box");
		bbBounds = boundingBoxText.getLocalBounds();
		boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
		boundingBoxText.setFillColor(sf::Color(255, 0, 0));
		boundingBoxText.setPosition((window->getSize().x / 8) * 1 - (window->getSize().x / 8) / 2, window->getSize().y - 20);
		window->draw(boundingBoxText);
	}

	if (drawAABB1) {
		boundingBoxText.setString("External AABB");
		bbBounds = boundingBoxText.getLocalBounds();
		boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
		boundingBoxText.setFillColor(sf::Color(0, 255, 0));
		boundingBoxText.setPosition((window->getSize().x / 8) * 2 - (window->getSize().x / 8) / 2, window->getSize().y - 20);
		window->draw(boundingBoxText);
	}

	if (drawAABB2) {
		boundingBoxText.setString("Internal AABB");
		bbBounds = boundingBoxText.getLocalBounds();
		boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
		boundingBoxText.setFillColor(sf::Color(0, 0, 255));
		boundingBoxText.setPosition((window->getSize().x / 8) * 3 - (window->getSize().x / 8) / 2, window->getSize().y - 20);
		window->draw(boundingBoxText);
	}

	if (drawAABB3) {
		boundingBoxText.setString("Average AABB");
		bbBounds = boundingBoxText.getLocalBounds();
		boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
		boundingBoxText.setFillColor(sf::Color(0, 255, 255));
		boundingBoxText.setPosition((window->getSize().x / 8) * 4 - (window->getSize().x / 8) / 2, window->getSize().y - 20);
		window->draw(boundingBoxText);
	}

	if (drawAABB4) {
		boundingBoxText.setString("True AABB");
		bbBounds = boundingBoxText.getLocalBounds();
		boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
		boundingBoxText.setFillColor(sf::Color(255, 0, 255));
		boundingBoxText.setPosition((window->getSize().x / 8) * 5 - (window->getSize().x / 8) / 2, window->getSize().y - 20);
		window->draw(boundingBoxText);
	}

	if (drawBS) {
		boundingBoxText.setString("Internal BS");
		bbBounds = boundingBoxText.getLocalBounds();
		boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
		boundingBoxText.setFillColor(sf::Color(255, 255, 0));
		boundingBoxText.setPosition((window->getSize().x / 8) * 6 - (window->getSize().x / 8) / 2, window->getSize().y - 20);
		window->draw(boundingBoxText);
	}

	if (drawBS2) {
		boundingBoxText.setString("External BS");
		bbBounds = boundingBoxText.getLocalBounds();
		boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
		boundingBoxText.setFillColor(sf::Color(255, 127, 0));
		boundingBoxText.setPosition((window->getSize().x / 8) * 7 - (window->getSize().x / 8) / 2, window->getSize().y - 20);
		window->draw(boundingBoxText);
	}

	if (drawBS3) {
		boundingBoxText.setString("True BS");
		bbBounds = boundingBoxText.getLocalBounds();
		boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
		boundingBoxText.setFillColor(sf::Color(127, 255, 0));
		boundingBoxText.setPosition((window->getSize().x / 8) * 8 - (window->getSize().x / 8) / 2, window->getSize().y - 20);
		window->draw(boundingBoxText);
	}
}

void UI::drawInfo() {
	window->pushGLStates();
	window->resetGLStates();

	fpsTime = fpsClock.getElapsedTime();

	while (time.asMilliseconds() + tick.asMilliseconds() < clock.getElapsedTime().asMilliseconds()) {
		if (displayInfo) {
			updateDebugInfo();
			updateFPS();
		}

		time += tick;
	}

	fpsClock.restart().asSeconds();
	
	if (displayInfo) {
		window->draw(debug);
		window->draw(fps);
		window->draw(frameTime);
		drawBoundingBoxText();
	}

	window->draw(crosshair);

	window->popGLStates();
}