#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <cmath>
#include <cstdlib>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "random.hpp"

class Asteroid {
private:
	glm::vec2 _position;
	float _radius;
	glm::vec2 _velocity;
	float _angle; //this will be just used in sfml so it is degrees

	std::string _file_path;

public:
	const std::string& file_path() const { return _file_path; }
	const glm::vec2& position() const { return this->_position; }
	float angle() { return this->_angle; }
	
	Asteroid(float w, float h)
		: _position(w*random_float(), h*random_float()),
		_velocity(random_float()*0.1-0.05, random_float()*0.1-0.05) {
		_angle = random_float()*360;
		_file_path = "./sprites/asteroid.png";
		_radius = 32.f;
	}
	Asteroid() = default;
	~Asteroid() = default;

public:
	void colide(Asteroid& asteroid) {
		float distance = glm::length(this->_position - asteroid._position);
		if (distance < asteroid._radius+this->_radius && distance >= 1) {
			float rest = asteroid._radius+this->_radius - distance;
			
			glm::vec2 v = this->_velocity;
			this->_velocity = asteroid._velocity;
			asteroid._velocity = v;

			this->_position += rest*glm::normalize(this->_velocity);
			asteroid._position += rest*glm::normalize(asteroid._velocity);
		}
	}

	void update(const float& dt, float width, float height, std::vector<Asteroid>& asteroids) {
		for (Asteroid& asteroid : asteroids) {
			this->colide(asteroid);
		}
		this->_position += this->_velocity*dt;
		this->_angle += this->_velocity.x;

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
};

#endif
