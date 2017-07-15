#include "ApplicationData.h"
#include "Controls.h"
#include "FighterStrings.h"

#include <iostream>

float ApplicationData::deltaTime = 1.f / 60.f;
SceneManager* ApplicationData::sceneManager = nullptr;

std::string selectedStage = "Ryu_Alpha";
std::string p1MainName = RYU;
int			p1MainAltColor = 1;
std::string p1SupportName = TON_POOH;
int			p1SupportAltColor = 2;
std::string p2MainName = RYU;
int			p2MainAltColor = 2;
std::string p2SupportName = SAKI;
int			p2SupportAltColor = 1;

float* gameSpeedPointer;
int* numberOfFramesPointer;


//std::pair<Controls::ControlType, int> ApplicationData::player1Controls = std::make_pair(Controls::ControlType::Keyboard, 1);
std::pair<Controls::ControlType, int> ApplicationData::player2Controls = std::make_pair(Controls::ControlType::Keyboard, 2);

std::pair<Controls::ControlType, int> ApplicationData::player1Controls = std::make_pair(Controls::ControlType::Controller, 0);
//std::pair<Controls::ControlType, int> ApplicationData::player2Controls = std::make_pair(Controls::ControlType::Keyboard, 2);

void ApplicationData::SetPlayerControls(int playerNumber, Controls::ControlType controlType, int controllerNumber) {
	if (1 == playerNumber)
		player1Controls = std::make_pair(controlType, controllerNumber);
	else if (2 == playerNumber)
		player2Controls = std::make_pair(controlType, controllerNumber);
	else
		std::cout << "Invalid playerNumber!" << std::endl;
}

void ApplicationData::SetGameSpeed(float gameSpeed, int numberOfFrames) {
	*gameSpeedPointer = gameSpeed;
	*numberOfFramesPointer = numberOfFrames;
}

float ApplicationData::GetGameSpeed() {
	return *gameSpeedPointer;
}

