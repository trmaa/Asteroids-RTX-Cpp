#ifndef STAR_HPP
#define STAR_HPP

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include "random.hpp"

class Star {
private:
	glm::vec3 _position;

public:
	const glm::vec3& position() const { return this->_position; }

	Star(float w, float h): _position(w*random_float(), h*random_float(), random_float()*2) {}
	Star() = default;
	~Star() = default;
};

#endif
