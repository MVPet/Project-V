#pragma once

#include <utility>
#include "Controls.h"
#include "SceneManager.h"
#include "SoundManager.h"

class ApplicationData {
public:
	static void SetPlayerControls(int playerNumber, Controls::ControlType controlType, int controllerNumber = 0);
	static void SetGameSpeed(float gameSpeed, int numberOfFrames);
	static float GetGameSpeed();

	static float deltaTime;
	static std::pair<Controls::ControlType, int> player1Controls;
	static std::pair<Controls::ControlType, int> player2Controls;
	
	static SceneManager* sceneManager;
};