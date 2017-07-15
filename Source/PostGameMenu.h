#pragma once

#include <SFML/Graphics.hpp>
#include "Controls.h"

class PostGameMenu {
public:
	PostGameMenu();
	~PostGameMenu();

	bool Update(Controls* p1Controls, Controls* p2Controls);
	void Draw(sf::RenderWindow* window);
	void SetPosition(sf::View currentView);

private:
	void UpdateCurrentOptionUI();
	void OptionSelected();

	sf::Texture p1CursorTexure;
	sf::Sprite p1CursorSprite;

	sf::Texture p2CursorTexure;
	sf::Sprite p2CursorSprite;

	sf::Texture backgroundTexure;
	sf::Sprite backgroundSprite;

	sf::Texture replayTextTexure;
	sf::Sprite replayTextSprite;

	sf::Texture charSelectTextTexture;
	sf::Sprite charSelectTextSprite;

	sf::Texture mainMenuTextTexure;
	sf::Sprite mainMenuTextSprite;

	int p1CurrentOption = 0;
	float lastP1Vert = 0;
	bool p1ConfirmHeld = true;
	bool p1Selected = false;

	int p2CurrentOption = 0;
	float lastP2Vert = 0;
	bool p2ConfirmHeld = true;
	bool p2Selected = false;
};