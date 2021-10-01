#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

#include<iostream>
using namespace std;

PlayScene::PlayScene()
{
	PlayScene::start();
	SoundManager::Instance().load("../Assets/audio/Bgm.mp3", "Bgm", SOUND_MUSIC);
	SoundManager::Instance().setMusicVolume(30);
	SoundManager::Instance().playMusic("Bgm", -1, 0);

}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	//Initial Positions
	m_pPlayer->getTransform()->position = glm::vec2(Xi, Yi);
	m_pWo->getTransform()->position = glm::vec2(Xi, Yi);

	//Other Variables
	//V = 95;
	//targetRange = 485.0f;000
	T += Tf - Ti;
	
	//Angle 
	angle = ((asin((targetRange * g) / powf(V, 2)) / 2));
	//angle = ((targetRange * g) / powf(V, 2));
	//angle = asin(angle);
	//angle = angle * 180.f / 3.14f;
	//angle = angle / 2;
	
	//angle = angle * 3.14f / 180.f;

	//cout << angle << endl;

	Vx = V * cos(angle);
	Vy = V * -1 * sin(angle);
	
	//Player Line Trayectory
	m_pWo->setvX(Vx);
	m_pWo->setvY(Vy);

	//Cooldown
	cd += T;

	//Launch
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE))
	{
		if (launch == false && cd > 1)
		{
			T = 0;
			launch = true;
			cd = 0;
		}
		else if (launch == true && cd > 1)
		{
			T = 0;
			m_pPlayer->getTransform()->position = glm::vec2(Xi, Yi);
			launch = false;
			cd = 0;
		}
	}

	//Launch
	if (launch == true)
	{
		m_pPlayer->getTransform()->position.x += Vx * T;
		m_pPlayer->getTransform()->position.y += Vy * T + 0.5 * g * powf(T, 2);
	}

	//Granade Stop
	if (m_pPlayer->getTransform()->position.y > Yi)
	{
		m_pPlayer->getTransform()->position = m_pSt->getTransform()->position;
	}
	
	updateDisplayList();

	//cout << t1 <<endl;

}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();
	
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	m_pBg = new Ship("../Assets/textures/Bg.png", "Bg");
	addChild(m_pBg);
	m_pBg->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, Config::SCREEN_HEIGHT * 0.525f);

	m_pSt = new Ship("../Assets/textures/St.png", "St");
	addChild(m_pSt);
	m_pSt->getTransform()->position = glm::vec2(Xi + targetRange, Yi);

	m_pPlayer = new Ship("../Assets/textures/Th.png","Th");
	addChild(m_pPlayer);

	m_pWo = new Ship("../Assets/textures/Woo.png", "Wo");
	addChild(m_pWo);

	m_pInstructionsLabel = new Label("Press Space bar to launch/reset", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 50.0f);
	addChild(m_pInstructionsLabel);

	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	//if(ImGui::Button("My Button"))
	//{
	//	std::cout << "My Button Pressed" << std::endl;
	//}

	//ImGui::Separator();

	if (ImGui::SliderFloat("Starting X", &Xi, 0.0f, 800.0f, "%.3f"))
	{
		m_pPlayer->getTransform()->position.x = Xi;
		m_pWo->getTransform()->position.x = Xi;
		m_pSt->getTransform()->position.x = Xi + targetRange;
	}
	if (ImGui::SliderFloat("Starting Y", &Yi, 0.0f, 600.0f, "%.3f"))
	{
		m_pPlayer->getTransform()->position.y = Yi;
		m_pWo->getTransform()->position.y = Yi;
		m_pSt->getTransform()->position.y = Yi;
	}
	if (ImGui::SliderFloat("Target Range", &targetRange, 35.0f, 800.0f, "%.3f"))
	{
		m_pSt->getTransform()->position.x = Xi + targetRange;
	}
	ImGui::SliderFloat("Launch Speed", &V, 70.0f, 300.0f, "%.3f");
	ImGui::SliderFloat("Acceleration Gravity", &g, -100.0f, 100.0f, "%.3f");

	//static float float3[3] = { 0.0f, 1.0f, 1.5f };
	//if(ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	//{
	//	std::cout << float3[0] << std::endl;
	//	std::cout << float3[1] << std::endl;
	//	std::cout << float3[2] << std::endl;
	//	std::cout << "---------------------------\n";
	//}
	
	ImGui::End();
}
