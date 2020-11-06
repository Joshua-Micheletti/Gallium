#include "ui.h"
#include "init.h"
#include "entity.h"
#include <stdlib.h>
#include <vector>
#include <string>
#include <math.h>
#include <sstream>
#include <iomanip>

// initialize the fields and formats the texts styles
UI::UI(sf::RenderWindow *window) {
	// get the window reference
	this->window = window;

	// setup the update clock
	this->tick = sf::milliseconds(1000 / 10);
	this->time = this->clock.getElapsedTime();

	// load the UI font
	if (!this->font.loadFromFile("../Fonts/segmono_boot.ttf")) {
		printf("COULDN'T LOAD FONT\n");
	}

	// set the UI font
	this->boundingBoxText.setFont(this->font);
	this->debug.setFont(this->font);
	this->fps.setFont(this->font);
	this->frameTime.setFont(this->font);

	// set the entity info style
	this->debug.setCharacterSize(16);
	this->debug.setFillColor(sf::Color::White);
	this->debug.setPosition(5, 5);
	this->debug.setOutlineThickness(1);
	this->debug.setOutlineColor(sf::Color::Black);

	// set the fps and frametime styles
	this->fps.setCharacterSize(16);
	this->fps.setFillColor(sf::Color::White);
	this->fps.setOutlineThickness(1);
	this->fps.setOutlineColor(sf::Color::Black);

	this->frameTime.setCharacterSize(16);
	this->frameTime.setFillColor(sf::Color::White);
	this->frameTime.setOutlineThickness(1);
	this->frameTime.setOutlineColor(sf::Color::Black);

	// set the bounding box text style
	this->boundingBoxText.setCharacterSize(16);
	this->boundingBoxText.setFillColor(sf::Color::Red);
	this->boundingBoxText.setOutlineThickness(1);
	this->boundingBoxText.setOutlineColor(sf::Color::Black);

	// design the crosshair
	this->crosshair.setRadius(2);
	this->crosshair.setFillColor(sf::Color(255, 255, 255));
	sf::FloatRect crosshairBounds = this->crosshair.getLocalBounds();
	this->crosshair.setOrigin(crosshairBounds.left + crosshairBounds.width / 2, crosshairBounds.top + crosshairBounds.height / 2);
	this->crosshair.setPosition(screenWidth / 2, screenHeight / 2);
	this->crosshair.setOutlineThickness(1);
	this->crosshair.setOutlineColor(sf::Color::Black);
}

// cycles all the entities retrieving the data for each, saves it into a string and sets the string to the info text
void UI::updateDebugInfo() {
	std::string text;
	for (int i = 0; i < entityBuffer.size(); i++) {
		text.append("> " +
			std::string(entityBuffer[i]->getName()) + ":\n  Position: (" +
			this->floatToString(entityBuffer[i]->getWorldPosition().x, 2) + ", " +
			this->floatToString(entityBuffer[i]->getWorldPosition().y, 2) + ", " +
			this->floatToString(entityBuffer[i]->getWorldPosition().z, 2) + ")\n  Rotation: (" +
			this->floatToString(entityBuffer[i]->getRotationFactor().x, 2) + ", " +
			this->floatToString(entityBuffer[i]->getRotationFactor().y, 2) + ", " +
			this->floatToString(entityBuffer[i]->getRotationFactor().z, 2) + ")\n  Scale: " +
			this->floatToString(entityBuffer[i]->getScalingFactor(), 2) + "\n\n");
	}
	this->debug.setString(text);
}

// calculates fps and frametime, passes the value to the text elements and repositions them accordingly
void UI::updateFPS() {
	this->fps.setString(this->floatToString(1.0f / this->fpsTime.asSeconds(), 0));
	this->frameTime.setString(this->floatToString(this->fpsTime.asMicroseconds() / 1000.0f, 2));

	sf::FloatRect fpsBounds = this->fps.getLocalBounds();
	this->fps.setOrigin(fpsBounds.left + fpsBounds.width, fpsBounds.top);
	this->fps.setPosition(this->window->getSize().x - 5, 5);

	fpsBounds = this->frameTime.getLocalBounds();
	this->frameTime.setOrigin(fpsBounds.left + fpsBounds.width, fpsBounds.top);
	this->frameTime.setPosition(this->window->getSize().x - 5, 20);
}

// checks which bounding boxes are being displayed and sets up the text accordingly and draws them
void UI::drawBoundingBoxText() {
	sf::FloatRect bbBounds;

	if (drawOBB) {
		this->boundingBoxText.setString("Object Bounding Box");
		bbBounds = this->boundingBoxText.getLocalBounds();
		this->boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
		this->boundingBoxText.setFillColor(sf::Color(255, 0, 0));
		this->boundingBoxText.setPosition((this->window->getSize().x / 8) * 1 - (this->window->getSize().x / 8) / 2, this->window->getSize().y - 20);
		this->window->draw(this->boundingBoxText);
	}

	if (drawAABB1) {
		this->boundingBoxText.setString("External AABB");
		bbBounds = this->boundingBoxText.getLocalBounds();
		this->boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
		this->boundingBoxText.setFillColor(sf::Color(0, 255, 0));
		this->boundingBoxText.setPosition((this->window->getSize().x / 8) * 2 - (this->window->getSize().x / 8) / 2, this->window->getSize().y - 20);
		this->window->draw(this->boundingBoxText);
	}

	if (drawAABB2) {
		this->boundingBoxText.setString("Internal AABB");
		bbBounds = this->boundingBoxText.getLocalBounds();
		this->boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
		this->boundingBoxText.setFillColor(sf::Color(0, 0, 255));
		this->boundingBoxText.setPosition((this->window->getSize().x / 8) * 3 - (this->window->getSize().x / 8) / 2, this->window->getSize().y - 20);
		this->window->draw(this->boundingBoxText);
	}

	if (drawAABB3) {
		this->boundingBoxText.setString("Average AABB");
		bbBounds = this->boundingBoxText.getLocalBounds();
		this->boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
		this->boundingBoxText.setFillColor(sf::Color(0, 255, 255));
		this->boundingBoxText.setPosition((this->window->getSize().x / 8) * 4 - (this->window->getSize().x / 8) / 2, this->window->getSize().y - 20);
		this->window->draw(this->boundingBoxText);
	}

	if (drawAABB4) {
		this->boundingBoxText.setString("True AABB");
		bbBounds = this->boundingBoxText.getLocalBounds();
		this->boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
		this->boundingBoxText.setFillColor(sf::Color(255, 0, 255));
		this->boundingBoxText.setPosition((this->window->getSize().x / 8) * 5 - (this->window->getSize().x / 8) / 2, this->window->getSize().y - 20);
		this->window->draw(this->boundingBoxText);
	}

	if (drawBS) {
		this->boundingBoxText.setString("Internal BS");
		bbBounds = this->boundingBoxText.getLocalBounds();
		this->boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
		this->boundingBoxText.setFillColor(sf::Color(255, 255, 0));
		this->boundingBoxText.setPosition((this->window->getSize().x / 8) * 6 - (this->window->getSize().x / 8) / 2, this->window->getSize().y - 20);
		this->window->draw(this->boundingBoxText);
	}

	if (drawBS2) {
		this->boundingBoxText.setString("External BS");
		bbBounds = this->boundingBoxText.getLocalBounds();
		this->boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
		this->boundingBoxText.setFillColor(sf::Color(255, 127, 0));
		this->boundingBoxText.setPosition((this->window->getSize().x / 8) * 7 - (this->window->getSize().x / 8) / 2, this->window->getSize().y - 20);
		this->window->draw(this->boundingBoxText);
	}

	if (drawBS3) {
		this->boundingBoxText.setString("True BS");
		bbBounds = this->boundingBoxText.getLocalBounds();
		this->boundingBoxText.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
		this->boundingBoxText.setFillColor(sf::Color(127, 255, 0));
		this->boundingBoxText.setPosition((this->window->getSize().x / 8) * 8 - (this->window->getSize().x / 8) / 2, this->window->getSize().y - 20);
		this->window->draw(this->boundingBoxText);
	}
}

std::string UI::floatToString(float number, int precision) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(precision) << number;
	std::string s = stream.str();
	return(s);
}

// just calls all the other methods, this method is public
void UI::drawInfo() {
	this->window->pushGLStates();
	this->window->resetGLStates();

	this->fpsTime = this->fpsClock.getElapsedTime();

	while (this->time.asMilliseconds() + this->tick.asMilliseconds() < this->clock.getElapsedTime().asMilliseconds()) {
		if (displayInfo) {
			this->updateDebugInfo();
			this->updateFPS();
		}

		this->time += this->tick;
	}

	this->fpsClock.restart().asSeconds();
	
	if (displayInfo) {
		this->window->draw(this->debug);
		this->window->draw(this->fps);
		this->window->draw(this->frameTime);
		this->drawBoundingBoxText();
	}

	this->window->draw(this->crosshair);

	this->window->popGLStates();
}

