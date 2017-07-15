#pragma once

#include <vector>
#include "Scene.h"
#include "Controls.h"

#include <SFML\Audio.hpp>

class TitleScreen : public Scene
{
public:
	TitleScreen();
	~TitleScreen();

	void Start();
	void UpdateEvent(sf::Event event);
	void Update();
	void Draw(sf::RenderWindow * window);

private:

	void UpdateCurrentOptionUI();
	void OptionSelected();

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Texture titleTextTexure;
	sf::Sprite titleTextSprite;

	sf::Texture startTextTexure;
	sf::Sprite startTextSprite;

	sf::Texture vsTextTexure;
	sf::Sprite vsTextSprite;

	sf::Texture trainingTextTexure;
	sf::Sprite trainingTextSprite;

	sf::Texture controlsTextTexure;
	sf::Sprite controlsTextSprite;

	sf::Texture controlsTexure;
	sf::Sprite controlsSprite;

	sf::Texture exitTextTexure;
	sf::Sprite exitTextSprite;

	sf::Texture controllerTexture;

	sf::Texture keyboard1Texture;

	sf::Texture keyboard2Texture;

	sf::Texture p1Texture;
	sf::Sprite p1Sprite;

	sf::Texture p2Texture;
	sf::Sprite p2Sprite;

	sf::Sprite p1ControlSprite;
	sf::Sprite p2ControlSprite;

	//bool titleMenu = false;

	int currentOption = 0;
	Controls* p1Controls;
	float lastP1Vert = 0;
	bool p1ConfirmHeld = true;
	Controls* p2Controls;
	float lastP2Vert = 0;
	bool p2ConfirmHeld = true;

	bool showControls = false;
	bool exitGame = false;

	sf::SoundBuffer cursorMoveSFX;
	sf::SoundBuffer cursorSelectSFX;
	sf::SoundBuffer cursorBackSFX;
	sf::Sound		cursorSound;
	sf::SoundBuffer titleSFX;
	sf::Sound		titleSound;
};

const std::string TITLE_SCREEN = "Title_Screen";
