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
	m_pPlayer->setvX(Vx);
	m_pPlayer->setvY(Vy);

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

	if (launch == true)
	{
		m_pPlayer->getTransform()->position.x += Vx * T;
		m_pPlayer->getTransform()->position.y += Vy * T + 0.5 * g * powf(T, 2);
	}


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



	m_pPlayer = new Ship();
	addChild(m_pPlayer);

	m_pSt = new Ship();
	addChild(m_pSt);
	m_pSt->getTransform()->position = glm::vec2(Xi + targetRange, Yi);

	///* Instructions Label */
	//m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	//m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 500.0f);

	//addChild(m_pInstructionsLabel);

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
		m_pSt->getTransform()->position.x = Xi + targetRange;
	}
	if (ImGui::SliderFloat("Starting Y", &Yi, 0.0f, 600.0f, "%.3f"))
	{
		m_pPlayer->getTransform()->position.y = Yi;
	}
	//if (ImGui::SliderFloat("Launch Elevation Angle", &launchElevationAngle, 0.0f, 360.0f, "%.3f"))
	//{
	//	m_pPlayer->setCurrentHeading(launchElevationAngle * -1);
	//}
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
