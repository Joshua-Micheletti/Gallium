#include "ui.h"
#include "init.h"
#include "entity.h"
#include <stdlib.h>
#include <vector>
#include <string>

UI::UI(sf::RenderWindow *window) {
	UI::window = window;
	debug.setCharacterSize(16);
	debug.setFillColor(sf::Color::White);
	debug.setPosition(5, 5);
	debug.setOutlineThickness(1);
	debug.setOutlineColor(sf::Color::Black);

	fps.setCharacterSize(16);
	fps.setFillColor(sf::Color::White);
	fps.setOutlineThickness(1);
	fps.setOutlineColor(sf::Color::Black);

	bb.setCharacterSize(16);
	bb.setOutlineThickness(1);
	bb.setOutlineColor(sf::Color::Black);

	if (!arial.loadFromFile("../Fonts/Arial.ttf")) {
		printf("COULDN'T LOAD FONT\n");
	}

	debug.setFont(arial);
	fps.setFont(arial);
	bb.setFont(arial);

	sf::FloatRect bbBounds = bb.getLocalBounds();

	bb.setOrigin(bbBounds.left + bbBounds.width / 2, bbBounds.top + bbBounds.height / 2);
	crosshair.setRadius(2);
	crosshair.setFillColor(sf::Color(255, 255, 255));
	sf::FloatRect crosshairBounds = crosshair.getLocalBounds();
	crosshair.setOrigin(crosshairBounds.left + crosshairBounds.width / 2, crosshairBounds.top + crosshairBounds.height / 2);
	crosshair.setPosition(screenWidth / 2, screenHeight / 2);
	crosshair.setOutlineThickness(1);
	crosshair.setOutlineColor(sf::Color::Black);
}

void UI::drawDebugInfo() {
	std::string text;
	for (int i = 0; i < entityBuffer.size(); i++) {
		text.append("> " + std::string(entityBuffer[i]->getName()) + ":\n  Position: (" + std::to_string(entityBuffer[i]->getWorldPosition().x) + ", " +
			std::to_string(entityBuffer[i]->getWorldPosition().y) + ", " +
			std::to_string(entityBuffer[i]->getWorldPosition().z) + ")\n  Rotation: (" +
			std::to_string(entityBuffer[i]->getRotationFactor().x) + ", " +
			std::to_string(entityBuffer[i]->getRotationFactor().y) + ", " +
			std::to_string(entityBuffer[i]->getRotationFactor().z) + ")\n  Scale: " +
			std::to_string(entityBuffer[i]->getScalingFactor()) + "\n\n");
	}
	debug.setString(text);
	window->draw(debug);
}

void UI::drawCrosshair() {
	window->draw(crosshair);
}

void UI::drawFPS() {
	sf::Time fpsTime = fpsClock.getElapsedTime();

	fps.setString(std::to_string((int)(1.0f / fpsTime.asSeconds())));

	fpsClock.restart().asSeconds();

	sf::FloatRect fpsBounds = fps.getLocalBounds();
	fps.setOrigin(fpsBounds.left + fpsBounds.width, fpsBounds.top);
	fps.setPosition(window->getSize().x - 5, 5);

	window->draw(fps);
}