#pragma once

#include <string>

#include "SplashScreen.h"
#include "TitleScreen.h"
#include "LocalVersus.h"
#include "VsCharSelect.h"
#include "TrainingCharSelect.h"
#include "Training.h"

static Scene* InitializeScene(std::string name)
{
	if (TITLE_SCREEN == name)
		return new TitleScreen();
	else if (LOCAL_VERSUS == name)
		return new LocalVersus();
	else if (VS_CHAR_SELECT == name)
		return new VsCharSelect();
	else if (TRAINING_CHAR_SELECT == name)
		return new TrainingCharSelect();
	else if (TRAINING == name)
		return new Training();
	else if (SPLASH_SCREEN == name)
		return new SplashScreen();

	return nullptr;
}