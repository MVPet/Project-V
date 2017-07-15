#include <iostream>

#include <SFML\System.hpp>

#include "GameManager.h"
#include "SceneManager.h"
#include "ApplicationData.h"

using namespace sf;

const float GameManager::TIME_PER_FRAME = 1.f / 60.f; // THE ATTEMPT AT FIXING THE FRAME PACING ISSUE

extern float* gameSpeedPointer;
extern int* numberOfFramesPointer;

GameManager::GameManager()
{
	window = new RenderWindow(VideoMode(1920, 1080), "Cap Vs Com");
	window->create(VideoMode(1920, 1080), "Cap Vs Com", Style::Fullscreen); // For fullscreen or to change settings at runtime will be used by options menu
	window->setKeyRepeatEnabled(false);
	//window->setFramerateLimit(60); // Just in case my logic doesn't work out
	sceneManager = new SceneManager();
	ApplicationData::sceneManager = sceneManager;
	updateTimer = 0.f;
}

GameManager::~GameManager()
{
	delete window;
	delete sceneManager;
}

void GameManager::run()
{
	int frameCount = 0;
	int drawFrameCount = 0;
	float oneSecCount = 0;

	// Check controllers (Here temporarily)
	if (sf::Joystick::isConnected(0)) {
		ApplicationData::SetPlayerControls(1, Controls::ControlType::Controller, 0);

		if (sf::Joystick::isConnected(1))
			ApplicationData::SetPlayerControls(2, Controls::ControlType::Controller, 1);
		else
			ApplicationData::SetPlayerControls(2, Controls::ControlType::Keyboard, 0);
	}
	else {
		ApplicationData::SetPlayerControls(1, Controls::ControlType::Keyboard, 0);

		if (sf::Joystick::isConnected(0))
			ApplicationData::SetPlayerControls(2, Controls::ControlType::Controller, 1);
		else
			ApplicationData::SetPlayerControls(2, Controls::ControlType::Keyboard, 1);
	}

	gameSpeedPointer = &gameSpeed;
	numberOfFramesPointer = &slowdownTimer;

	sceneManager->SetCurrentScene(SPLASH_SCREEN);
	//sceneManager->SetCurrentScene(TITLE_SCREEN);
	//sceneManager->SetCurrentScene(VS_CHAR_SELECT);
	//sceneManager->SetCurrentScene(TRAINING_CHAR_SELECT);
	//sceneManager->SetCurrentScene(LOCAL_VERSUS);
	//sceneManager->SetCurrentScene(TRAINING);
	Clock updateClock;

	//gameSpeed = 0.25;

	while (window->isOpen())
	{
		float asSec = updateClock.restart().asSeconds();
		drawSlowdownTimer += asSec;
		updateTimer += asSec;
		oneSecCount += asSec;

		if ((TIME_PER_FRAME / gameSpeed) < updateTimer) // Sets the game logic to 60fps...
		{
			updateTimer = 0.f;
			frameCount++;

			if (inFocus)
				sceneManager->Update();

			Event event;
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::LostFocus)
					inFocus = false;

				if (event.type == sf::Event::GainedFocus)
					inFocus = true;

				if (Event::Closed == event.type)
					window->close();

				if (inFocus)
					sceneManager->UpdateEvent(event);
			}

			if (0 < slowdownTimer) {
				slowdownTimer--;
				if (0 == slowdownTimer) {
					gameSpeed = 1.f;
				}
			}

			/*
			if (1 <= oneSecCount) {
				std::cout << "fps: " << frameCount << std::endl;
				std::cout << "fps: " << drawFrameCount << std::endl;
				frameCount = 0;
				drawFrameCount = 0;
				oneSecCount = 0;
			}
			*/
		}

		// Should be drawn once per frame not at unlimited frames
		if (inFocus) {
			if (0 >= slowdownTimer || (0 < slowdownTimer && (TIME_PER_FRAME / gameSpeed) < drawSlowdownTimer)) {
				drawSlowdownTimer = 0;
				window->clear();
				sceneManager->Draw(window); // ...But should draw at 60+ fps
				sf::RenderStates rendState;
				rendState.shader = &testShader;
				window->display();
				drawFrameCount++;
			}
		}
	}
}