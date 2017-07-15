#pragma once

#include "PauseMenu.h"
#include "Utilities.h"
#include "ApplicationData.h"
#include "Fight.h"
#include <iostream>

PauseMenu::PauseMenu() {
	std::string filename = "Textures/Misc/PauseMenu/";

	if (!p1PauseTextTexure.loadFromFile(filename + "P1PauseText.png"))
		std::cout << "CANNOT LOAD TITLE TEXT" << std::endl;
	p1PauseTextSprite.setTexture(p1PauseTextTexure);
	p1PauseTextSprite.setOrigin(GetTextureCenter(&p1PauseTextTexure));
	p1PauseTextSprite.setScale(0.35f, 0.35f);

	if (!p1CursorTexture.loadFromFile(filename + "P1Cursor.png"))
		std::cout << "CANNOT LOAD TITLE TEXT" << std::endl;
	p1CursorSprite.setTexture(p1CursorTexture);
	p1CursorSprite.setOrigin(GetTextureCenter(&p1CursorTexture));
	p1CursorSprite.setScale(0.35f, 0.35f);

	if (!p2PauseTextTexure.loadFromFile(filename + "P2PauseText.png"))
		std::cout << "CANNOT LOAD TITLE TEXT" << std::endl;
	p2PauseTextSprite.setTexture(p2PauseTextTexure);
	p2PauseTextSprite.setOrigin(GetTextureCenter(&p2PauseTextTexure));
	p2PauseTextSprite.setScale(0.35f, 0.35f);

	if (!p2CursorTexture.loadFromFile(filename + "P2Cursor.png"))
		std::cout << "CANNOT LOAD TITLE TEXT" << std::endl;
	p2CursorSprite.setTexture(p2CursorTexture);
	p2CursorSprite.setOrigin(GetTextureCenter(&p2CursorTexture));
	p2CursorSprite.setScale(0.35f, 0.35f);

	if (!backgroundMenuTexure.loadFromFile(filename + "Background.png"))
		std::cout << "CANNOT LOAD PAUSE BACKGROUND" << std::endl;
	backgroundMenuSprite.setTexture(backgroundMenuTexure);
	backgroundMenuSprite.setOrigin(GetTextureCenter(&backgroundMenuTexure));
	backgroundMenuSprite.setScale(0.35f, 0.35f);

	if (!resumeTextTexure.loadFromFile(filename + "ResumeText.png"))
		std::cout << "CANNOT LOAD TITLE TEXT" << std::endl;
	resumeTextSprite.setTexture(resumeTextTexure);
	resumeTextSprite.setOrigin(GetTextureCenter(&resumeTextTexure));
	resumeTextSprite.setScale(0.35f, 0.35f);

	if (!commandListTextTexure.loadFromFile(filename + "CommandListText.png"))
		std::cout << "CANNOT LOAD TITLE TEXT" << std::endl;
	commandListTextSprite.setTexture(commandListTextTexure);
	commandListTextSprite.setOrigin(GetTextureCenter(&commandListTextTexure));
	commandListTextSprite.setScale(0.35f, 0.35f);

	if (!charSelTextTexure.loadFromFile(filename + "CharacterSelectText.png"))
		std::cout << "CANNOT LOAD TITLE TEXT" << std::endl;
	charSelTextSprite.setTexture(charSelTextTexure);
	charSelTextSprite.setOrigin(GetTextureCenter(&charSelTextTexure));
	charSelTextSprite.setScale(0.35f, 0.35f);

	if (!exitTextTexure.loadFromFile(filename + "ExitText.png"))
		std::cout << "CANNOT LOAD TITLE TEXT" << std::endl;
	exitTextSprite.setTexture(exitTextTexure);
	exitTextSprite.setOrigin(GetTextureCenter(&exitTextTexure));
	exitTextSprite.setScale(0.35f, 0.35f);
}

PauseMenu::~PauseMenu() {
}

bool PauseMenu::Update(Controls* p1Controls, Controls* p2Controls) {

	int yAxis;

	if (1 == playerNumPause) {
		yAxis = p1Controls->GetVerticalAxis();
		if (0 != yAxis && yAxis != lastP1Vert)
			currentOption += 1 * yAxis;
		lastP1Vert = yAxis;
	}

	if (2 == playerNumPause) {
		yAxis = p2Controls->GetVerticalAxis();
		if (0 != yAxis && yAxis != lastP2Vert)
			currentOption += 1 * yAxis;
		lastP2Vert = yAxis;
	}

	if (currentOption > 3)
		currentOption = 0;
	else if (currentOption < 0)
		currentOption = 3;

	UpdateCurrentOptionUI();

	if (1 == playerNumPause && p1Controls->isActionPressed(Controls::Actions::Light)) {
		if (!p1ConfirmHeld) {
			p1ConfirmHeld = true;
			return OptionSelected();
		}
	}
	else
		p1ConfirmHeld = false;

	if (2 == playerNumPause && p2Controls->isActionPressed(Controls::Actions::Light)) {
		if (!p2ConfirmHeld) {
			p2ConfirmHeld = true;
			return OptionSelected();
		}
	}
	else
		p2ConfirmHeld = false;

	return true;
}

void PauseMenu::SetPosition(sf::View currentView) {
	backgroundMenuSprite.setPosition(currentView.getCenter());
	p1PauseTextSprite.setPosition(backgroundMenuSprite.getPosition().x, backgroundMenuSprite.getPosition().y - 35.f);
	p2PauseTextSprite.setPosition(backgroundMenuSprite.getPosition().x, backgroundMenuSprite.getPosition().y - 35.f);
	resumeTextSprite.setPosition(backgroundMenuSprite.getPosition().x, backgroundMenuSprite.getPosition().y - 15.f);
	commandListTextSprite.setPosition(backgroundMenuSprite.getPosition().x, backgroundMenuSprite.getPosition().y - 0.f);
	charSelTextSprite.setPosition(backgroundMenuSprite.getPosition().x, backgroundMenuSprite.getPosition().y + 15.f);
	exitTextSprite.setPosition(backgroundMenuSprite.getPosition().x, backgroundMenuSprite.getPosition().y + 30.f);

	commandListSprite.setPosition(backgroundMenuSprite.getPosition().x, backgroundMenuSprite.getPosition().y - 0.f);
}

void PauseMenu::Draw(sf::RenderWindow* window) {
	if (commandListOpen) {
		window->draw(commandListSprite);
		return;
	}

	window->draw(backgroundMenuSprite);
	if (2 == playerNumPause) {
		window->draw(p2PauseTextSprite);
		window->draw(p2CursorSprite);
	}
	else {
		window->draw(p1PauseTextSprite);
		window->draw(p1CursorSprite);
	}

	window->draw(resumeTextSprite);
	window->draw(commandListTextSprite);
	window->draw(charSelTextSprite);
	window->draw(exitTextSprite);
}

void PauseMenu::UpdateCurrentOptionUI() {
	switch (currentOption)
	{
	case 0:
		resumeTextSprite.setColor(sf::Color::Yellow);
		commandListTextSprite.setColor(sf::Color::White);
		charSelTextSprite.setColor(sf::Color::White);
		exitTextSprite.setColor(sf::Color::White);
		p1CursorSprite.setPosition(resumeTextSprite.getPosition());
		p2CursorSprite.setPosition(resumeTextSprite.getPosition());
		break;
	case 1:
		resumeTextSprite.setColor(sf::Color::White);
		commandListTextSprite.setColor(sf::Color::Yellow);
		charSelTextSprite.setColor(sf::Color::White);
		exitTextSprite.setColor(sf::Color::White);
		p1CursorSprite.setPosition(commandListTextSprite.getPosition());
		p2CursorSprite.setPosition(commandListTextSprite.getPosition());
		break;
	case 2:
		resumeTextSprite.setColor(sf::Color::White);
		commandListTextSprite.setColor(sf::Color::White);
		charSelTextSprite.setColor(sf::Color::Yellow);
		exitTextSprite.setColor(sf::Color::White);
		p1CursorSprite.setPosition(charSelTextSprite.getPosition());
		p2CursorSprite.setPosition(charSelTextSprite.getPosition());
		break;
	case 3:
		resumeTextSprite.setColor(sf::Color::White);
		commandListTextSprite.setColor(sf::Color::White);
		charSelTextSprite.setColor(sf::Color::White);
		exitTextSprite.setColor(sf::Color::Yellow);
		p1CursorSprite.setPosition(exitTextSprite.getPosition());
		p2CursorSprite.setPosition(exitTextSprite.getPosition());
		break;
	default:
		break;
	}
}

bool PauseMenu::OptionSelected() {
	if (commandListOpen) {
		commandListOpen = false;
		return true;
	}

	switch (currentOption)
	{
	case 0:
		return false;
	case 1:
		commandListOpen = true;
		return true;
	case 2:
		Fight::StopAllNoise();
		ApplicationData::sceneManager->SetCurrentScene(VS_CHAR_SELECT);
		return false;
	case 3:
		Fight::StopAllNoise();
		ApplicationData::sceneManager->SetCurrentScene(TITLE_SCREEN);
		return false;
	default:
		return false;
	}
}

void PauseMenu::SetPlayerNumber(int numberWhoPaused, sf::Texture& commandListTexture) {
	playerNumPause = numberWhoPaused;
	commandListSprite.setTexture(commandListTexture);
	commandListSprite.setOrigin(GetTextureCenter(&commandListTexture));
	commandListSprite.setScale(0.5f, 0.5f);
	p1ConfirmHeld = true;
	p2ConfirmHeld = true;
	currentOption = 0;
}
