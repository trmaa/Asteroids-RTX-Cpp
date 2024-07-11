#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "asteroid.hpp"
#include "player.hpp"
#include "star.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <string>
#include <vector>

class Window : public sf::RenderWindow {
private:
	sf::Font _font;

	struct Scene {
		float width;
		float height;

		Player player;
		std::vector<Star> star;
		std::vector<Asteroid> asteroid;

		Scene(float x, float y): player() {
			width = x;
			height = y;

			star = std::vector<Star>(x*y/4000);
			for (Star& s : star) {
				s = Star(x, y);
			}

			asteroid = std::vector<Asteroid>(1);
			for (Asteroid& a : asteroid) {
				a = Asteroid(x, y);
			}
		}
		~Scene() = default;
	};
	Scene _scene;

public:
	Window(std::string title, int w, int h)
		: _scene(w, h) {
		if (this->isOpen()) {
			return; 
		}
		this->create(sf::VideoMode::getDesktopMode(), title, sf::Style::Fullscreen);
		sf::View fixedView(sf::FloatRect(0, 0, w, h));
		this->setView(fixedView);

		this->_font.loadFromFile("./fonts/pixelmix.ttf");

		this->setFramerateLimit(60);
	}
	~Window() = default;

public:
	void update(sf::Event& event, float& dt) {
		if (!this->isOpen()) {
			return;
		}
		this->clear();	

		for (int i = -1; i <= 1; i++) { //to surround and dont let the player know how little map is
		for (int j = -1; j <= 1; j++) {

		for (Star& star : this->_scene.star) {
			sf::RectangleShape shape;
			shape.setSize(sf::Vector2f(1.f/star.position().z, 1.f/star.position().z));
			shape.setRotation(45);

			glm::vec3 pos = star.position();
			pos -= glm::vec3(this->_scene.player.position(),0) 
				- glm::vec3(this->_scene.width/2 + this->_scene.width*i, 
				this->_scene.height/2 + this->_scene.height*j, 0);

			shape.setPosition(
					(pos.x-this->_scene.width/2)/pos.z+this->_scene.width/2, 
					(pos.y-this->_scene.height/2)/pos.z+this->_scene.height/2);
			shape.setFillColor(sf::Color(255,255,255));
			this->draw(shape);
		}

		for (Asteroid& asteroid : this->_scene.asteroid) {
			asteroid.update(dt, this->_scene.width, this->_scene.height);
			sf::Texture texture;
			if (texture.loadFromFile(asteroid.file_path())) {
				sf::Sprite sprite(texture);
				sprite.setOrigin(texture.getSize().x/2.f, texture.getSize().y/2.f);
				
				glm::vec2 pos = asteroid.position();
				pos -= this->_scene.player.position();

				sprite.setPosition(
					pos.x + this->_scene.width*i, 
					pos.y + this->_scene.height*j);
				sprite.setRotation(asteroid.angle());
				this->draw(sprite);
			}
		}

		}
		}

		this->_scene.player.update(event, dt, this->_scene.width, this->_scene.height);
		sf::Texture texture;
        if (texture.loadFromFile(_scene.player.file_path())) {
            sf::Sprite sprite(texture);
			sprite.setOrigin(texture.getSize().x/2.f, texture.getSize().y/2.f);
            sprite.setPosition(this->_scene.width/2, this->_scene.height/2);
			//sprite.setPosition(this->_scene.player.position().x, this->_scene.player.position().y);
			sprite.setRotation(_scene.player.angle()*180/3.14159f);
            this->draw(sprite);
        }
		
		sf::Text fps_text;
		fps_text.setString(std::to_string(1/(dt-1)));
		fps_text.setPosition(16, 16);
		fps_text.setFont(this->_font);
		fps_text.setCharacterSize(20);
		this->draw(fps_text);
		
		this->display();
	}
};

#endif
