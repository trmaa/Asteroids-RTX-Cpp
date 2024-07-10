#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

inline float random_float() {
	static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    
    return dis(gen);
}

#endif
