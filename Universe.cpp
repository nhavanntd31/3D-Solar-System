#include "Universe.h"

void Universe::updateVelocity(float deltaTime)
{
	for (unsigned int i = 0; i < planetList.size(); i++)
	{
		
			Planet* body = planetList.at(i);
			glm::vec3 fDirection = glm::normalize(star->getOrigin() - body->getCurrentOrigin());
			float force = g * star->getMass() * body->getMass() / body->getDistanceToStar() / body->getDistanceToStar();
			glm::vec3 velocity = force * fDirection / 1.0f * deltaTime;
			//velocity *= deltaTime;
			body->addVelocity(velocity);
	}
}

void Universe::updatePosition(float deltaTime)
{
	for (unsigned int i = 0; i < planetList.size(); i++)
	{
		Planet* body = planetList.at(i);
		body->addMove(body->getCurrentVelocity() * deltaTime);
		body->addPointOrbit();
	}
}
