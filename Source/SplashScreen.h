#pragma once

#include "Scene.h"
#include <vector>

class SplashScreen : public Scene {
public:
	SplashScreen();
	~SplashScreen();

	void Start();
	void UpdateEvent(sf::Event event);
	void Update();
	void Draw(sf::RenderWindow * window);

private:
	const int NUM_OF_SPLASH_SCREENS = 2;
	const int TIME_PER_SPLASH_SCREEN = 180;

	void FadeOut();
	void FadeIn();

	int splashScreenTimer = TIME_PER_SPLASH_SCREEN;
	int currentSplashScreen = 0;

	bool fadeOut = true;
	bool fadeIn = false;
	int fadeRate = 5;

	sf::Texture fadeTexture;
	sf::Sprite fadeSprite;

	sf::Texture disclaimerTexture;
	sf::Texture buyTexture;

	sf::Sprite splashSprites[2];
};

const std::string SPLASH_SCREEN = "Splash_Screen";