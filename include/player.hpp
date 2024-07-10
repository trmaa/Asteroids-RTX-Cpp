#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <glm/glm.hpp>
#include <string>

class Player {
private:	
	glm::vec2 _position;
	float _angle;

	glm::vec2 _velocity;
	
	float _speed = 0.2f;
	float _max_speed = 10.f;
	float _min_speed = 0.1f;
	float _friction = 0.95f;
	
	std::string _file_path;

	struct Controller {
		bool up, down, left, right, space;

		void update(sf::Event& event) {
			if (event.type == sf::Event::KeyPressed) {
				event.key.code == sf::Keyboard::Up ? this->up = true : 0;
				event.key.code == sf::Keyboard::Down ? this->down = true : 0;
				event.key.code == sf::Keyboard::Right ? this->right = true : 0;
				event.key.code == sf::Keyboard::Left ? this->left = true : 0;
				event.key.code == sf::Keyboard::Space ? this->space = true : 0;
			}
			if (event.type == sf::Event::KeyReleased) {
				event.key.code == sf::Keyboard::Up ? this->up = false : 0;
				event.key.code == sf::Keyboard::Down ? this->down = false : 0;
				event.key.code == sf::Keyboard::Right ? this->right = false : 0;
				event.key.code == sf::Keyboard::Left ? this->left = false : 0;
				event.key.code == sf::Keyboard::Space ? this->space = false : 0;	
			}		
		}
	};
	Controller _controller;

private:
	void _move(float& dt, float width, float height) {
		if (this->_controller.up) {
			this->_velocity += this->_speed 
				* glm::vec2(std::cos(this->_angle), std::sin(this->_angle)) * dt;
		}
		if (this->_controller.down) {
			this->_velocity -= this->_speed 
				* glm::vec2(std::cos(this->_angle), std::sin(this->_angle)) * dt;
		}

		if (this->_controller.right) {
			this->_angle += 0.5f * this->_speed * dt;
		}
		if (this->_controller.left) {
			this->_angle -= 0.5f * this->_speed * dt;
		}

		this->_velocity *= this->_friction * dt;	
		
		float modul = this->_velocity.length();
		if (modul > this->_max_speed) {
			this->_velocity = glm::normalize(this->_velocity) * this->_max_speed;
		}
		if (modul < this->_min_speed && modul > -this->_min_speed && modul != 0.f) {
			this->_velocity *= 0.f;
		}

		this->_position += this->_velocity;

		if (this->_position.x > width) {
			this->_position.x = 0;
		}
		if (this->_position.x < 0) {
			this->_position.x = width;
		}
		if (this->_position.y > height) {
			this->_position.y = 0;
		}
		if (this->_position.y < 0) {
			this->_position.y = height;
		}
	}

public:
	const std::string& file_path() const { return _file_path; }
    const glm::vec2& position() const { return _position; }
	float angle() { return _angle; }
	
	Player(std::string f_path, float x, float y)
		: _position(x, y) {
		this->_file_path = f_path;
	}
	Player(): _position(192, 108), _file_path("./sprites/player.png") {}
	~Player() = default;

public:
	void update(sf::Event& event, float& dt, float width, float height) {
		this->_controller.update(event);
		this->_move(dt, width, height);
	}
};

#endif
