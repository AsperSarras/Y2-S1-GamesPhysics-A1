#pragma once
#ifndef __SHIP__
#define __SHIP__

#include "TextureManager.h"
#include <glm/vec4.hpp>

#include "Agent.h"

class Ship final : public Agent
{
public:
	Ship();
	~Ship();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;

	void turnRight();
	void turnLeft();
	void moveForward();
	void moveBack();

	void move();

	// getters
	float getMaxSpeed() const;
	float getvX() const;
	float getvY() const;
	glm::vec2 finalPosition(float a, float b);

	// setters
	void setMaxSpeed(float newSpeed);
	void setvX(float vX);
	void setvY(float vy);

private:
	void m_checkBounds();
	void m_reset();

	float m_maxSpeed;
	float m_turnRate;

	//A2
	float vX;
	float vY;

};


#endif /* defined (__SHIP__) */

