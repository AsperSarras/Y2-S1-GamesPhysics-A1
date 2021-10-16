#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "ship.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Ship* m_pBg;

	Ship* m_pPlayer;
	Ship* m_pWo;
	Ship* m_pSt;
	bool m_playerFacingRight;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;

	//A1 Variables
	float Xi; //
	float Yi; //
	float angle; //
	//float mass;
	//float g = 9.8f * 50.0f; //
	float V = 95.0f; //
	float Vx; //
	float Vy; //
	float targetRange = 485.0f; //
	float Tf = 0.016f; //
	float Ti = 0.0f; //
	float T; //

	//A2 Variables
	float scale = 50.0f;
	float mass = 12.8f;
	float g = 9.8f * scale;
	float mg = mass*g;
	float rampRise = 3.0f * scale;
	float rampRun = 4.0f * scale;
	float rampPosX = 100;
	float groundPos = 500;
	float kFriction = 0.42f;

	//Ramp
	float rampLenght;
	float rampAngle;
	float netForceX;
	float netForceY;
	float accelX;
	float accelY;

	
	//Ground
	float frictionForce;
	float timeGround;
	float ininitialVelocityFloor;
	float newX;
	float accelXGround;
	float netForceXGround;
	float netForceYGround;
	float timeToStop;
	float distanceToStop;

	float ax;

	float cd;
	bool launch = false;
	bool ground = false;
	bool stop = false;
};

#endif /* defined (__PLAY_SCENE__) */