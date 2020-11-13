#include "Libs/lib.h"

int main(void) {
	sf::RenderWindow* window = setup();
	Renderer renderer;
	EventHandler eventHandler(window);
	UI interface(window, renderer, &eventHandler);

	while (window->isOpen()) {
		eventHandler.routine();
		renderer.render();
		interface.drawInfo();
		window->display();
	}

	return(0);
}
