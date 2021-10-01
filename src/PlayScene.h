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
	float Xi = 50.0f; //
	float Yi = 500.0f; //
	float angle; //
	float mass;
	float g = 9.8f; //
	float V = 95.0f; //
	float Vx; //
	float Vy; //
	float targetRange = 485.0f; //
	float Tf = 0.016f; //
	float Ti = 0.0f; //
	float T; //

	float cd;
	bool launch = false;
};

#endif /* defined (__PLAY_SCENE__) */