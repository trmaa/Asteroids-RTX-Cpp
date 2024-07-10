#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "player.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <string>

class Window : public sf::RenderWindow {
private:
	struct Scene {
		Player player;
		Scene(): player() {}
		~Scene() = default;
	};
	Scene _scene;

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
