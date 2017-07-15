#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

#include "StageStrings.h"

static sf::Texture* GetStageSampleTextures() {
	using namespace sf;

	Texture* textureList = new Texture[NUM_OF_STAGES];
	std::string* stageNames = GetAllStageStrings();
	std::string filepath = "Textures/Stages/";

	for (int i = 0; i < NUM_OF_STAGES; i++) {
		if (!textureList[i].loadFromFile(filepath + stageNames[i] + "/Sample.png"))
			std::cout << "CANNOT LOAD " << stageNames[i] << "'S SAMPLE IMAGE" << std::endl;
	}

	return textureList;
}