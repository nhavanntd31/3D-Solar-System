#pragma once

#include "Celestial.h"

class Universe {	
public:
	std::vector<Planet*> planetList;
	Star* star;
	Star* skyBox;
	void addBody(Planet* body) { planetList.push_back(body); };
	void updateVelocity(float deltaTime);
	void updatePosition(float deltaTime);
	void setStar(Star* star) { this->star = star; }
	void setSky(Star* sky) { this->skyBox = sky; };
	bool isBool;
};