#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Window.hpp>
#include <cstdio>
#include "window.hpp"

void loop();

Window window("Asteroids", 384, 216);

sf::Event event;
sf::Clock clck;
sf::Time elapsed;
float dt;

int main() {
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		elapsed = clck.restart();
        dt = elapsed.asSeconds() + 1;        

		loop();
	}
}
void loop() {
	window.update(event, dt);
}
