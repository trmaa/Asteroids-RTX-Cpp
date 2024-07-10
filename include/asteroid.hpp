#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <glm/glm.hpp>
#include <string>
#include "random.hpp"

class Asteroid {
private:
	glm::vec2 _position;
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
	}
	Asteroid() = default;
	~Asteroid() = default;

public:
	void update(float& dt, float width, float height) {
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
