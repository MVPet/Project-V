#pragma once

#include "PostGameMenu.h"
#include "Utilities.h"
#include "ApplicationData.h"
#include "Fight.h"
#include <iostream>

PostGameMenu::PostGameMenu() {
	std::string filename = "Textures/Misc/PostGameMenu/";

	if (!backgroundTexure.loadFromFile(filename + "Background.png"))
		std::cout << "CANNOT LOAD BACKGROUND TEXTURE" << std::endl;
	backgroundSprite.setTexture(backgroundTexure);
	backgroundSprite.setOrigin(GetTextureCenter(&backgroundTexure));
	backgroundSprite.setScale(0.35f, 0.35f);

	if (!p1CursorTexure.loadFromFile(filename + "P1Cursor.png"))
		std::cout << "CANNOT LOAD P1 CURSOR" << std::endl;
	p1CursorSprite.setTexture(p1CursorTexure);
	p1CursorSprite.setOrigin(GetTextureCenter(&p1CursorTexure));
	p1CursorSprite.setScale(0.35f, 0.35f);

	if (!p2CursorTexure.loadFromFile(filename + "P2Cursor.png"))
		std::cout << "CANNOT LOAD P2 CURSOR" << std::endl;
	p2CursorSprite.setTexture(p2CursorTexure);
	p2CursorSprite.setOrigin(GetTextureCenter(&p2CursorTexure));
	p2CursorSprite.setScale(0.35f, 0.35f);

	if (!replayTextTexure.loadFromFile(filename + "ReplayText.png"))
		std::cout << "CANNOT LOAD FIGHT AGAIN TEXT" << std::endl;
	replayTextSprite.setTexture(replayTextTexure);
	replayTextSprite.setOrigin(GetTextureCenter(&replayTextTexure));
	replayTextSprite.setScale(0.35f, 0.35f);

	if (!charSelectTextTexture.loadFromFile(filename + "CharSelectText.png"))
		std::cout << "CANNOT LOAD CHAR SELECT TEXT" << std::endl;
	charSelectTextSprite.setTexture(charSelectTextTexture);
	charSelectTextSprite.setOrigin(GetTextureCenter(&charSelectTextTexture));
	charSelectTextSprite.setScale(0.35f, 0.35f);

	if (!mainMenuTextTexure.loadFromFile(filename + "MainMenuText.png"))
		std::cout << "CANNOT LOAD MAIN MENU TEXT" << std::endl;
	mainMenuTextSprite.setTexture(mainMenuTextTexure);
	mainMenuTextSprite.setOrigin(GetTextureCenter(&mainMenuTextTexure));
	mainMenuTextSprite.setScale(0.35f, 0.35f);
}

PostGameMenu::~PostGameMenu() {
}

bool PostGameMenu::Update(Controls* p1Controls, Controls* p2Controls) {

	int yAxis;

	if (!p1Selected) {
		yAxis = p1Controls->GetVerticalAxis();
		if (0 != yAxis && yAxis != lastP1Vert)
			p1CurrentOption += 1 * yAxis;
		lastP1Vert = yAxis;

		if (p1CurrentOption > 2)
			p1CurrentOption = 2;
		else if (p1CurrentOption < 0)
			p1CurrentOption = 0;

		if (p1Controls->isActionPressed(Controls::Actions::Light)) {
			if (!p1ConfirmHeld) {
				p1ConfirmHeld = true;
				p1Selected = true;
				OptionSelected();
				return false;
			}
		}
		else
			p1ConfirmHeld = false;
	}

	if (!p2Selected) {
		yAxis = p2Controls->GetVerticalAxis();
		if (0 != yAxis && yAxis != lastP2Vert)
			p2CurrentOption += 1 * yAxis;
		lastP2Vert = yAxis;

		if (p2CurrentOption > 2)
			p2CurrentOption = 2;
		else if (p2CurrentOption < 0)
			p2CurrentOption = 0;

		if (p2Controls->isActionPressed(Controls::Actions::Light)) {
			if (!p2ConfirmHeld && !p2Selected) {
				p2ConfirmHeld = true;
				p2Selected = true;
				OptionSelected();
				return false;
			}
		}
		else
			p2ConfirmHeld = false;
	}

	UpdateCurrentOptionUI();

	return true;
}

void PostGameMenu::SetPosition(sf::View currentView) {
	backgroundSprite.setPosition(currentView.getCenter());
	replayTextSprite.setPosition(backgroundSprite.getPosition().x, backgroundSprite.getPosition().y - 20.f);
	charSelectTextSprite.setPosition(replayTextSprite.getPosition().x, backgroundSprite.getPosition().y - 0.f);
	mainMenuTextSprite.setPosition(charSelectTextSprite.getPosition().x, backgroundSprite.getPosition().y + 20.f);

	p1CursorSprite.setPosition(replayTextSprite.getPosition());
	p2CursorSprite.setPosition(replayTextSprite.getPosition());
}

void PostGameMenu::Draw(sf::RenderWindow* window) {
	window->draw(backgroundSprite);
	window->draw(replayTextSprite);
	window->draw(charSelectTextSprite);
	window->draw(mainMenuTextSprite);

	window->draw(p1CursorSprite);
	window->draw(p2CursorSprite);
}

void PostGameMenu::UpdateCurrentOptionUI() {
	replayTextSprite.setColor(sf::Color::White);
	charSelectTextSprite.setColor(sf::Color::White);
	mainMenuTextSprite.setColor(sf::Color::White);

	switch (p1CurrentOption)
	{
	case 0:
		replayTextSprite.setColor(sf::Color::Yellow);
		p1CursorSprite.setPosition(replayTextSprite.getPosition());
		break;
	case 1:
		charSelectTextSprite.setColor(sf::Color::Yellow);
		p1CursorSprite.setPosition(charSelectTextSprite.getPosition());
		break;
	case 2:
		mainMenuTextSprite.setColor(sf::Color::Yellow);
		p1CursorSprite.setPosition(mainMenuTextSprite.getPosition());
		break;
	default:
		break;
	}

	switch (p2CurrentOption)
	{
	case 0:
		replayTextSprite.setColor(sf::Color::Yellow);
		p2CursorSprite.setPosition(replayTextSprite.getPosition());
		break;
	case 1:
		charSelectTextSprite.setColor(sf::Color::Yellow);
		p2CursorSprite.setPosition(charSelectTextSprite.getPosition());
		break;
	case 2:
		mainMenuTextSprite.setColor(sf::Color::Yellow);
		p2CursorSprite.setPosition(mainMenuTextSprite.getPosition());
		break;
	default:
		break;
	}
}

void PostGameMenu::OptionSelected() {
	int maxOption = (p1CurrentOption > p2CurrentOption) ? p1CurrentOption : p2CurrentOption;

	if (!p1Selected || !p2Selected)
		return;

	switch (maxOption)
	{
	case 0:
		Fight::StopAllNoise();
		ApplicationData::sceneManager->SetCurrentScene(LOCAL_VERSUS);
		return;
	case 1:
		Fight::StopAllNoise();
		ApplicationData::sceneManager->SetCurrentScene(VS_CHAR_SELECT);
		return;
	case 2:
		Fight::StopAllNoise();
		ApplicationData::sceneManager->SetCurrentScene(TITLE_SCREEN);
	default:
		return;
	}
}