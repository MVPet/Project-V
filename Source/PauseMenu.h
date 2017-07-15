#pragma once

#include <SFML/Graphics.hpp>
#include "Controls.h"

class PauseMenu
{
public:
	PauseMenu();
	~PauseMenu();

	bool Update(Controls* p1Controls, Controls* p2Controls);
	void Draw(sf::RenderWindow* window);
	void SetPosition(sf::View currentView);
	void SetPlayerNumber(int numberWhoPaused, sf::Texture& commandListTexture);

private:
	void UpdateCurrentOptionUI();
	bool OptionSelected();

	sf::Texture p1PauseTextTexure;
	sf::Sprite p1PauseTextSprite;

	sf::Texture p1CursorTexture;
	sf::Sprite p1CursorSprite;

	sf::Texture p2PauseTextTexure;
	sf::Sprite p2PauseTextSprite;

	sf::Texture p2CursorTexture;
	sf::Sprite p2CursorSprite;

	sf::Texture backgroundMenuTexure;
	sf::Sprite backgroundMenuSprite;

	sf::Texture resumeTextTexure;
	sf::Sprite resumeTextSprite;

	sf::Texture commandListTextTexure;
	sf::Sprite commandListTextSprite;

	sf::Texture charSelTextTexure;
	sf::Sprite charSelTextSprite;

	sf::Texture exitTextTexure;
	sf::Sprite exitTextSprite;

	sf::Sprite commandListSprite;

	int currentOption = 0;
	float lastP1Vert = 0;
	bool p1ConfirmHeld = true;
	float lastP2Vert = 0;
	bool p2ConfirmHeld = true;
	int playerNumPause = 0;

	bool commandListOpen = false;
};
