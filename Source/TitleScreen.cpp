#include <iostream>

#include "TitleScreen.h"
#include "VsCharSelect.h"
#include "ApplicationData.h"
#include "Utilities.h"

TitleScreen::TitleScreen() {
}

TitleScreen::~TitleScreen() {
	delete p1Controls;
	delete p2Controls;
}

void TitleScreen::Start() {
	std::string filename = "Textures/Scenes/TitleScreen/";

	if (!backgroundTexture.loadFromFile(filename + "Background.png"))
		std::cout << "CANNOT LOAD LOGO" << std::endl;
	backgroundSprite.setTexture(backgroundTexture);

	if (!titleTextTexure.loadFromFile(filename + "Logo.png"))
		std::cout << "CANNOT LOAD LOGO" << std::endl;
	titleTextSprite.setTexture(titleTextTexure);
	titleTextSprite.setOrigin(GetTextureCenter(&titleTextTexure));
	titleTextSprite.setPosition(640.f, 180.f);

	if (!vsTextTexure.loadFromFile(filename + "VsText.png"))
		std::cout << "CANNOT LOAD VS TEXT" << std::endl;
	vsTextSprite.setTexture(vsTextTexure);
	vsTextSprite.setOrigin(GetTextureCenter(&vsTextTexure));
	vsTextSprite.setPosition(640.f, 350.f);
	vsTextSprite.setColor(sf::Color::Yellow);

	if (!trainingTextTexure.loadFromFile(filename + "TrainingText.png"))
		std::cout << "CANNOT LOAD START TEXT" << std::endl;
	trainingTextSprite.setTexture(trainingTextTexure);
	trainingTextSprite.setOrigin(GetTextureCenter(&trainingTextTexure));
	trainingTextSprite.setPosition(640.f, vsTextSprite.getPosition().y + 75.f);

	if (!controlsTextTexure.loadFromFile(filename + "ControlsText.png"))
		std::cout << "CANNOT LOAD VS TEXT" << std::endl;
	controlsTextSprite.setTexture(controlsTextTexure);
	controlsTextSprite.setOrigin(GetTextureCenter(&controlsTextTexure));
	controlsTextSprite.setPosition(640.f, trainingTextSprite.getPosition().y + 65.f);
	controlsTextSprite.setColor(sf::Color::Yellow);

	if (!exitTextTexure.loadFromFile(filename + "ExitText.png"))
		std::cout << "CANNOT LOAD START TEXT" << std::endl;
	exitTextSprite.setTexture(exitTextTexure);
	exitTextSprite.setOrigin(GetTextureCenter(&exitTextTexure));
	exitTextSprite.setPosition(640.f, controlsTextSprite.getPosition().y + 65.f);

	if (!controlsTexure.loadFromFile(filename + "Controls.png"))
		std::cout << "CANNOT LOAD START TEXT" << std::endl;
	controlsSprite.setTexture(controlsTexure);

	p1Controls = new Controls(ApplicationData::player1Controls);
	p2Controls = new Controls(ApplicationData::player2Controls);

	if (!controllerTexture.loadFromFile(filename + "Controller.png"))
		std::cout << "CANNOT LOAD START TEXT" << std::endl;

	if (!keyboard1Texture.loadFromFile(filename + "Keyboard1.png"))
		std::cout << "CANNOT LOAD START TEXT" << std::endl;

	if (!keyboard2Texture.loadFromFile(filename + "Keyboard2.png"))
		std::cout << "CANNOT LOAD START TEXT" << std::endl;


	if (!p1Texture.loadFromFile(filename + "P1.png"))
		std::cout << "CANNOT LOAD START TEXT" << std::endl;
	p1Sprite.setTexture(p1Texture);
	p1Sprite.setPosition(550.f, 645.f);
	p1ControlSprite.setPosition(600.f, 645.f);

	if (!p2Texture.loadFromFile(filename + "P2.png"))
		std::cout << "CANNOT LOAD START TEXT" << std::endl;
	p2Sprite.setTexture(p2Texture);
	p2Sprite.setPosition(550.f, 680.f);
	p2ControlSprite.setPosition(600.f, 680.f);

	switch (ApplicationData::player1Controls.first)
	{
	case Controls::ControlType::Controller:
		p1ControlSprite.setTexture(controllerTexture);
		break;
	case Controls::ControlType::Keyboard:
		p1ControlSprite.setTexture(keyboard1Texture);
		break;
	default:
		break;
	}

	switch (ApplicationData::player2Controls.first)
	{
	case Controls::ControlType::Controller:
		p2ControlSprite.setTexture(controllerTexture);
		break;
	case Controls::ControlType::Keyboard:
		if (Controls::ControlType::Keyboard == ApplicationData::player1Controls.first)
			p2ControlSprite.setTexture(keyboard2Texture);
		else
			p2ControlSprite.setTexture(keyboard1Texture);
		break;
	default:
		break;
	}


	if (!titleSFX.loadFromFile("SFX/titleSFX.wav"))
		std::cout << "CANNOT LOAD TITLE SFX" << std::endl;

	if (!cursorSelectSFX.loadFromFile("SFX/cursorSelectSFX.wav"))
		std::cout << "CANNOT LOAD cursorSelectSFX SFX" << std::endl;
	if (!cursorBackSFX.loadFromFile("SFX/cursorBackSFX.wav"))
		std::cout << "CANNOT LOAD cursorBackSFX SFX" << std::endl;
	if (!cursorMoveSFX.loadFromFile("SFX/cursorMoveSFX.wav"))
		std::cout << "CANNOT LOAD cursorMoveSFX SFX" << std::endl;

	cursorSound.setVolume(50);
	titleSound.setBuffer(titleSFX);
	titleSound.setVolume(50);
	titleSound.play();
}

void TitleScreen::UpdateEvent(sf::Event event) {

	return;

	if (sf::Event::JoystickButtonPressed == event.type ||
		sf::Event::KeyPressed == event.type)
	{
		p1ConfirmHeld = true;
		p2ConfirmHeld = true;
		//titleMenu = true;
	}

}

void TitleScreen::Update() {
	//if (!titleMenu)
		//return;

	if (!showControls) {
		int yAxis;

		yAxis = p1Controls->GetVerticalAxis();
		if (0 != yAxis && yAxis != lastP1Vert) {
			cursorSound.setBuffer(cursorMoveSFX);
			cursorSound.play();
			currentOption += 1 * yAxis;
		}
		lastP1Vert = yAxis;

		yAxis = p2Controls->GetVerticalAxis();
		if (0 != yAxis && yAxis != lastP2Vert) {
			cursorSound.setBuffer(cursorMoveSFX);
			cursorSound.play();
			currentOption += 1 * yAxis;
		}
		lastP2Vert = yAxis;

		if (currentOption > 3)
			currentOption = 0;
		else if (currentOption < 0)
			currentOption = 3;

		UpdateCurrentOptionUI();

		if (p1Controls->isActionPressed(Controls::Actions::Light)) {
			if (!p1ConfirmHeld) {
				p1ConfirmHeld = true;
				OptionSelected();
				return;
			}
		}
		else
			p1ConfirmHeld = false;

		if (p2Controls->isActionPressed(Controls::Actions::Light)) {
			if (!p2ConfirmHeld) {
				p2ConfirmHeld = true;
				OptionSelected();
				return;
			}
		}
		else
			p2ConfirmHeld = false;
	}
	else
	{
		if (p1Controls->isActionPressed(Controls::Actions::Heavy)) {
			if (!p1ConfirmHeld) {
				p1ConfirmHeld = true;
				showControls = false;
				cursorSound.setBuffer(cursorBackSFX);
				cursorSound.play();
				return;
			}
		}
		else
			p1ConfirmHeld = false;

		if (p2Controls->isActionPressed(Controls::Actions::Heavy)) {
			if (!p2ConfirmHeld) {
				p2ConfirmHeld = true;
				showControls = false;
				cursorSound.setBuffer(cursorBackSFX);
				cursorSound.play();
				return;
			}
		}
		else
			p2ConfirmHeld = false;
	}
}

void TitleScreen::Draw(sf::RenderWindow* window) {
	// restore the default view
	//window->setView(window->getDefaultView());

	sf::View temp;
	temp.setSize(sf::Vector2f(1280, 720));
	temp.setCenter(sf::Vector2f(640, 360));
	window->setView(temp);

	if (!showControls) {
		window->draw(backgroundSprite);
		window->draw(titleTextSprite);
		window->draw(vsTextSprite);
		window->draw(trainingTextSprite);
		window->draw(controlsTextSprite);
		window->draw(exitTextSprite);
		window->draw(p1Sprite);
		window->draw(p1ControlSprite);
		window->draw(p2Sprite);
		window->draw(p2ControlSprite);

		if (exitGame) window->close();
	}
	else
	{
		window->draw(controlsSprite);
	}
}

void TitleScreen::UpdateCurrentOptionUI() {
	switch (currentOption)
	{
	case 0:
		vsTextSprite.setColor(sf::Color::Yellow);
		trainingTextSprite.setColor(sf::Color::White);
		controlsTextSprite.setColor(sf::Color::White);
		exitTextSprite.setColor(sf::Color::White);
		break;
	case 1:
		vsTextSprite.setColor(sf::Color::White);
		trainingTextSprite.setColor(sf::Color::Yellow);
		controlsTextSprite.setColor(sf::Color::White);
		exitTextSprite.setColor(sf::Color::White);
		break;
	case 2:
		vsTextSprite.setColor(sf::Color::White);
		trainingTextSprite.setColor(sf::Color::White);
		controlsTextSprite.setColor(sf::Color::Yellow);
		exitTextSprite.setColor(sf::Color::White);
		break;
	case 3:
		vsTextSprite.setColor(sf::Color::White);
		trainingTextSprite.setColor(sf::Color::White);
		controlsTextSprite.setColor(sf::Color::White);
		exitTextSprite.setColor(sf::Color::Yellow);
		break;
	default:
		break;
	}
}

void TitleScreen::OptionSelected() {
	switch (currentOption)
	{
	case 0:
		cursorSound.stop();
		titleSound.stop();
		ApplicationData::sceneManager->SetCurrentScene(VS_CHAR_SELECT);
		break;
	case 1:
		cursorSound.stop();
		titleSound.stop();
		ApplicationData::sceneManager->SetCurrentScene(TRAINING_CHAR_SELECT);
		break;
	case 2:
		showControls = true;
		break;
	case 3:
		cursorSound.stop();
		titleSound.stop();
		exitGame = true;
		break;
	default:
		break;
	}

	cursorSound.setBuffer(cursorSelectSFX);
	cursorSound.play();
}

