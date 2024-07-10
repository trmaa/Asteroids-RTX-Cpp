#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "player.hpp"
#include "star.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <string>
#include <vector>

class Window : public sf::RenderWindow {
private:
	struct Scene {
		Player player;
		std::vector<Star> star;

		Scene(float x, float y): player() {
			star = std::vector<Star>(x*y/2000);
			for (Star& s : star) {
				s = Star(x, y);
			}
		}
		~Scene() = default;
	};
	Scene _scene = Scene(394, 219);

public:
	Window(std::string title, int w, int h) {
		if (this->isOpen()) {
			return; 
		}
		this->create(sf::VideoMode::getDesktopMode(), title, sf::Style::Fullscreen);
		sf::View fixedView(sf::FloatRect(0, 0, w, h));
		this->setView(fixedView);
		this->setFramerateLimit(60);
	}
	~Window() = default;

public:
	void update(sf::Event& event, float& dt) {
		if (!this->isOpen()) {
			return;
		}
		this->clear();

		for (Star& star : this->_scene.star) {
			sf::RectangleShape shape;
			shape.setSize(sf::Vector2f(1.f/star.position().z, 1.f/star.position().z));
			shape.setRotation(45);

			glm::vec3 pos = star.position();
			pos -= glm::vec3(this->_scene.player.position(),0)-glm::vec3(192, 108, 0);

			shape.setPosition((pos.x-192)/pos.z+192, (pos.y-108)/pos.z+108);
			shape.setFillColor(sf::Color(255,255,255));
			this->draw(shape);
		}

		this->_scene.player.update(event, dt);
		sf::Texture texture;
        if (texture.loadFromFile(_scene.player.file_path())) {
            sf::Sprite sprite(texture);
			sprite.setOrigin(texture.getSize().x/2.f, texture.getSize().y/2.f);
            sprite.setPosition(_scene.player.position().x, _scene.player.position().y);
            sprite.setRotation(_scene.player.angle()*180/3.14159f);
            this->draw(sprite);
        }

		this->display();
	}
};

#endif
