#include "SplashScreen.h"
#include "ApplicationData.h"
#include <iostream>

SplashScreen::SplashScreen() {
}

SplashScreen::~SplashScreen() {
}

void SplashScreen::Start() {
	std::string filename = "Textures/Scenes/SplashScreens/";

	if (!fadeTexture.loadFromFile(filename + "Fade.png"))
		std::cout << "CANNOT LOAD FADE" << std::endl;
	fadeSprite.setTexture(fadeTexture);
	fadeSprite.setColor(sf::Color(255, 255, 255, 255));

	if (!buyTexture.loadFromFile(filename + "Buy.png"))
		std::cout << "CANNOT LOAD BUY" << std::endl;
	if (!disclaimerTexture.loadFromFile(filename + "Disclaimer.png"))
		std::cout << "CANNOT LOAD DISCLAIMER" << std::endl;

	splashSprites[0].setTexture(disclaimerTexture);
	splashSprites[1].setTexture(buyTexture);
}

void SplashScreen::UpdateEvent(sf::Event event) {
}

void SplashScreen::Update() {
	if (NUM_OF_SPLASH_SCREENS <= currentSplashScreen) {
		ApplicationData::sceneManager->SetCurrentScene(TITLE_SCREEN);
		return;
	}

	if (fadeOut)
		FadeOut();
	else if (fadeIn)
		FadeIn();
	else {
		splashScreenTimer--;

		if (0 >= splashScreenTimer)
			fadeIn = true;
	}

}

void SplashScreen::Draw(sf::RenderWindow * window) {
	sf::View temp;
	temp.setSize(sf::Vector2f(1280, 720));
	temp.setCenter(sf::Vector2f(640, 360));
	window->setView(temp);

	if (NUM_OF_SPLASH_SCREENS > currentSplashScreen) {
		window->draw(splashSprites[currentSplashScreen]);
		window->draw(fadeSprite);
	}
}

void SplashScreen::FadeOut() {
	int a = fadeSprite.getColor().a;
	a -= (1 * fadeRate);
	if (0 >= a)
	{
		a = 0;
		fadeOut = false;
		splashScreenTimer = TIME_PER_SPLASH_SCREEN;
	}

	fadeSprite.setColor(sf::Color(255, 255, 255, a));
}

void SplashScreen::FadeIn() {
	int a = fadeSprite.getColor().a;
	a += (1 * fadeRate);
	if (255 <= a)
	{
		a = 255;
		fadeOut = true;
		fadeIn = false;
		currentSplashScreen++;
	}

	fadeSprite.setColor(sf::Color(255, 255, 255, a));
}