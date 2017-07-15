#include "VsCharSelect.h"
#include "FighterStrings.h"
#include "Utilities.h"
#include "ApplicationData.h"
#include "StageInitializer.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

extern std::string p1MainName;
extern int	p1MainAltColor;
extern std::string p1SupportName;
extern int	p1SupportAltColor;
extern std::string p2MainName;
extern int	p2MainAltColor;
extern std::string p2SupportName;
extern int	p2SupportAltColor;
extern std::string selectedStage;

VsCharSelect::VsCharSelect() {
}

VsCharSelect::~VsCharSelect() {
	delete playableFighters;
	delete supportFighters;
	delete p1Controls;
	delete p2Controls;
	delete[] stageSampleTextures;
}

void VsCharSelect::Start() {
	camera.setSize(1280, 720);
	camera.zoom(0.35f);

	if (!backgroundTexture.loadFromFile("Textures/Scenes/CharSelect/Background.png"))
		std::cout << "CANNOT LOAD P1 CURSOR TEXTURE" << std::endl;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setOrigin(GetTextureCenter(&backgroundTexture));
	backgroundSprite.setPosition(camera.getCenter());
	backgroundSprite.setScale(0.35f, 0.35f);

	if (!charTitleTexture.loadFromFile("Textures/Scenes/CharSelect/CharTitle.png"))
		std::cout << "CANNOT LOAD P1 CURSOR TEXTURE" << std::endl;
	charTitleSprite.setTexture(charTitleTexture);
	charTitleSprite.setOrigin(GetTextureCenter(&charTitleTexture));
	charTitleSprite.setPosition(camera.getCenter().x, camera.getCenter().y - 115.f);
	charTitleSprite.setScale(0.35f, 0.35f);

	if (!stageTitleTexture.loadFromFile("Textures/Scenes/CharSelect/StageTitle.png"))
		std::cout << "CANNOT LOAD P1 CURSOR TEXTURE" << std::endl;
	stageTitleSprite.setTexture(stageTitleTexture);
	stageTitleSprite.setOrigin(GetTextureCenter(&stageTitleTexture));
	stageTitleSprite.setPosition(camera.getCenter().x, camera.getCenter().y - 115.f);
	stageTitleSprite.setScale(0.35f, 0.35f);

	if (!p1CursorTexture.loadFromFile("Textures/Scenes/CharSelect/P1Cursor.png"))
		std::cout << "CANNOT LOAD P1 CURSOR TEXTURE" << std::endl;
	p1CursorSprite.setTexture(p1CursorTexture);
	p1CursorSprite.setOrigin(GetTextureCenter(&p1CursorTexture));

	if (!p1Rand1CursorTexture.loadFromFile("Textures/Scenes/CharSelect/P1Rand1Cursor.png"))
		std::cout << "CANNOT LOAD P1 CURSOR TEXTURE" << std::endl;
	p1Rand1CursorSprite.setTexture(p1Rand1CursorTexture);
	p1Rand1CursorSprite.setOrigin(GetTextureCenter(&p1Rand1CursorTexture));

	if (!p1Rand2CursorTexture.loadFromFile("Textures/Scenes/CharSelect/P1Rand2Cursor.png"))
		std::cout << "CANNOT LOAD P1 CURSOR TEXTURE" << std::endl;
	p1Rand2CursorSprite.setTexture(p1Rand2CursorTexture);
	p1Rand2CursorSprite.setOrigin(GetTextureCenter(&p1Rand2CursorTexture));

	if (!p2Rand1CursorTexture.loadFromFile("Textures/Scenes/CharSelect/P2Rand1Cursor.png"))
		std::cout << "CANNOT LOAD P1 CURSOR TEXTURE" << std::endl;
	p2Rand1CursorSprite.setTexture(p2Rand1CursorTexture);
	p2Rand1CursorSprite.setOrigin(GetTextureCenter(&p2Rand1CursorTexture));

	if (!p2Rand2CursorTexture.loadFromFile("Textures/Scenes/CharSelect/P2Rand2Cursor.png"))
		std::cout << "CANNOT LOAD P1 CURSOR TEXTURE" << std::endl;
	p2Rand2CursorSprite.setTexture(p2Rand2CursorTexture);
	p2Rand2CursorSprite.setOrigin(GetTextureCenter(&p2Rand2CursorTexture));

	if (!p2CursorTexture.loadFromFile("Textures/Scenes/CharSelect/P2Cursor.png"))
		std::cout << "CANNOT LOAD P2 CURSOR TEXTURE" << std::endl;
	p2CursorSprite.setTexture(p2CursorTexture);
	p2CursorSprite.setOrigin(GetTextureCenter(&p2CursorTexture));

	if (!arrowTexture.loadFromFile("Textures/Scenes/CharSelect/Arrow.png"))
		std::cout << "CANNOT LOAD ARROW TEXTURE" << std::endl;
	leftArrowSprite.setTexture(arrowTexture);
	leftArrowSprite.setOrigin(GetTextureCenter(&arrowTexture));
	leftArrowSprite.setPosition(camera.getCenter().x - 90.f, camera.getCenter().y + 75.f);
	leftArrowSprite.setScale(-0.35f, 0.35f);
	rightArrowSprite.setTexture(arrowTexture);
	rightArrowSprite.setOrigin(GetTextureCenter(&arrowTexture));
	rightArrowSprite.setPosition(camera.getCenter().x + 90.f, camera.getCenter().y + 75.f);
	rightArrowSprite.setScale(0.35f, 0.35f);

	if (!assistTextTexture.loadFromFile("Textures/Scenes/CharSelect/AssistText.png"))
		std::cout << "CANNOT LOAD CHAR SELECT PORTRAIT" << std::endl;
	assistTextSprite.setTexture(assistTextTexture);
	assistTextSprite.setOrigin(sf::Vector2f(GetTextureCenter(&assistTextTexture).x, GetTextureCenter(&assistTextTexture).y * 2.f)); // Make Origin on text the bottom (allows for multi line names)
	assistTextSprite.setPosition(camera.getCenter().x, camera.getCenter().y + 125.f);
	assistTextSprite.setScale(0.5f, 0.5f);

	stageSampleTextures = GetStageSampleTextures();
	currentStageOptionSprite.setTexture(stageSampleTextures[0]);
	currentStageOptionSprite.setOrigin(GetTextureCenter(&stageSampleTextures[0]));
	currentStageOptionSprite.setPosition(sf::Vector2f(camera.getCenter().x, camera.getCenter().y + 75.f));
	currentStageOptionSprite.setScale(sf::Vector2f(0.30f, 0.30f));

	playableFighters = new FighterCharSelect[3];	// SHOULD USE A CONST FOR THIS
	playableFighters[0].Load(RYU);
	playableFighters[0].SetPortraitPosition(sf::Vector2f(camera.getCenter().x, camera.getCenter().y + 50.f), 1, -1);
	playableFighters[1].Load(RSELECT1);
	playableFighters[1].SetPortraitPosition(sf::Vector2f(camera.getCenter().x, camera.getCenter().y + 50.f), 0, -1);
	playableFighters[2].Load(KYOSUKE);
	playableFighters[2].SetPortraitPosition(sf::Vector2f(camera.getCenter().x, camera.getCenter().y + 50.f), 1, 1);

	supportFighters = new FighterCharSelect[3];		// SHOULD USE A CONST FOR THIS
	supportFighters[0].Load(SAKI, 80.f);
	supportFighters[0].SetPortraitPosition(sf::Vector2f(camera.getCenter().x, camera.getCenter().y + 95.f), 0.75f, -1);
	supportFighters[1].Load(RSELECT2);
	supportFighters[1].SetPortraitPosition(sf::Vector2f(camera.getCenter().x, camera.getCenter().y + 95.f), 0, -1);
	supportFighters[2].Load(TON_POOH, 100.f);
	supportFighters[2].SetPortraitPosition(sf::Vector2f(camera.getCenter().x, camera.getCenter().y + 95.f), 0.75f, 1);

	p1Main = playableFighters[p1CursorPosition.x];
	p1Main.SetXScale(1);
	p1Main.SetAnimationPosition(sf::Vector2f(camera.getCenter().x - 75.f, camera.getCenter().y - 110.f));
	p1Support = playableFighters[p1CursorPosition.x];
	p1Support.SetXScale(1);
	p1Support.SetAnimationPosition(sf::Vector2f(camera.getCenter().x - 150.f, camera.getCenter().y - 110.f));
	p1CursorSprite.setPosition(playableFighters[p1CursorPosition.x].GetPortraitPosition());
	p1CursorSprite.setScale((0 < p1CursorPosition.x) ? -1.f : 1.f, 1.f);

	p2Main = playableFighters[p2CursorPosition.x];
	p2Main.SetXScale(-1);
	p2Main.SetAnimationPosition(sf::Vector2f(camera.getCenter().x + 75.f, camera.getCenter().y - 110.f));
	p2Support = playableFighters[p2CursorPosition.x];
	p2Support.SetXScale(-1);
	p2Support.SetAnimationPosition(sf::Vector2f(camera.getCenter().x + 150.f, camera.getCenter().y - 110.f));
	p2CursorSprite.setPosition(playableFighters[p2CursorPosition.x].GetPortraitPosition());
	p2CursorSprite.setScale((0 < p2CursorPosition.x) ? -1.f : 1.f, 1.f);

	p1Controls = new Controls(ApplicationData::player1Controls);
	p2Controls = new Controls(ApplicationData::player2Controls);


	if (!charSelectMusic.openFromFile("Music/CharSelect.wav"))
		printf("CANNOT LOAD MUSIC: CharSelect\n");

	charSelectMusic.setVolume(50);
	charSelectMusic.play();
	charSelectMusic.setLoop(true);

	if (!cursorSelectSFX.loadFromFile("SFX/cursorSelectSFX.wav"))
		std::cout << "CANNOT LOAD cursorSelectSFX SFX" << std::endl;

	if (!cursorBackSFX.loadFromFile("SFX/cursorBackSFX.wav"))
		std::cout << "CANNOT LOAD cursorBackSFX SFX" << std::endl;

	if (!cursorMoveSFX.loadFromFile("SFX/cursorMoveSFX.wav"))
		std::cout << "CANNOT LOAD cursorMoveSFX SFX" << std::endl;

	p1Sound.setVolume(50);
	p2Sound.setVolume(50);
}

void VsCharSelect::UpdateEvent(sf::Event event) {
}

void VsCharSelect::Update() {
	if (sceneDone)
		return;

	if (!p1SupportSelected || !p2SupportSelected) {
		if (!CheckP1CharInputs())
			return;
		if (!CheckP2CharInputs())
			return;
	}
	else {
		if (!CheckP1StageInputs())
			return;
		if (!CheckP2StageInputs())
			return;
	}

	p1Main.Update();
	if (p1MainSelected) p1Support.Update();
	p2Main.Update();
	if (p2MainSelected) p2Support.Update();
}

bool VsCharSelect::CheckP1CharInputs() {
	int yAxis, xAxis;
	bool selectionChanged = false;

	if (!p1SupportSelected) {
		xAxis = p1Controls->GetHorizontalAxis();
		if (0 != xAxis && xAxis != lastP1Horiz) {
			p1Sound.setBuffer(cursorMoveSFX);
			p1Sound.play();
			p1CursorPosition.x += 1 * xAxis;
			selectionChanged = true;
		}
		lastP1Horiz = xAxis;

		yAxis = p1Controls->GetVerticalAxis();
		if (p1MainSelected && 0 != yAxis && yAxis != lastP1Vert) {
			p1Sound.setBuffer(cursorMoveSFX);
			p1Sound.play();
			p1CursorPosition.y += 1 * yAxis;
			selectionChanged = true;
		}
		lastP1Vert = yAxis;
	}

	if (selectionChanged)
		UpdateP1UI();

	if (p1Controls->isActionPressed(Controls::Actions::Light)) {
		if (!p1ConfirmHeld) {
			p1ConfirmHeld = true;
			if (!p1MainSelected) {
				if (1 == p1CursorPosition.x) {
					p1CursorPosition.x = GetRandomPlayable(1);
					UpdateP1UI();
				}
				p1Sound.setBuffer(cursorSelectSFX);
				p1Sound.play();
				p1MainSelected = true;
				//p1Support = p1Main;
				p1Main.Selected();
				p2Support = playableFighters[1];
				p1CursorPosition.x = 1;
				UpdateP1UI();
			}
			else if (!p1SupportSelected) {
				if (1 == p1CursorPosition.x) {
					if (1 == p1CursorPosition.y)
						p1CursorPosition.x = GetRandomSupport(1);
					else
						p1CursorPosition.x = GetRandomPlayable(1);

					UpdateP1UI();
				}
				p1Sound.setBuffer(cursorSelectSFX);
				p1Sound.play();
				p1SupportSelected = true;
				p1Support.Selected();
			}
			return true;
		}
	}
	else
		p1ConfirmHeld = false;

	if (p1Controls->isActionPressed(Controls::Actions::Heavy)) {
		if (!p1CancelHeld) {
			p1CancelHeld = true;
			if (p1SupportSelected) {
				p1SupportSelected = false;
				p1Support.Unselected();
				p1Sound.setBuffer(cursorBackSFX);
				p1Sound.play();
			}
			else if (p1MainSelected) {
				p1MainSelected = false;
				p1Main.Unselected();
				p1CursorPosition.y = 0;
				UpdateP1UI();
				p1Sound.setBuffer(cursorBackSFX);
				p1Sound.play();
			}
			else {
				charSelectMusic.stop();
				//charSelectSound.stop();
				p1Sound.stop();
				p2Sound.stop();
				ApplicationData::sceneManager->SetCurrentScene(TITLE_SCREEN);
				return false;
			}
			return true;
		}
	}
	else
		p1CancelHeld = false;

	return true;
}

bool VsCharSelect::CheckP1StageInputs() {
	int yAxis, xAxis;

	xAxis = p1Controls->GetHorizontalAxis();
	if (0 != xAxis && xAxis != lastP1Horiz) {
		currentStageOption += 1 * xAxis;
		if (0 > currentStageOption)
			currentStageOption = NUM_OF_STAGES - 1;
		else if ((NUM_OF_STAGES - 1) < currentStageOption)
			currentStageOption = 0;
		currentStageOptionSprite.setTexture(stageSampleTextures[currentStageOption]);
		p1Sound.setBuffer(cursorMoveSFX);
		p1Sound.play();
	}
	lastP1Horiz = xAxis;

	if (p1Controls->isActionPressed(Controls::Actions::Light)) {
		if (!p1ConfirmHeld) {
			p1ConfirmHeld = true;
			p1Sound.setBuffer(cursorSelectSFX);
			p1Sound.play();
			OnToTheFight();
			return false;
		}
	}
	else
		p1ConfirmHeld = false;

	if (p1Controls->isActionPressed(Controls::Actions::Heavy)) {
		if (!p1CancelHeld) {
			p1CancelHeld = true;
			if (p1SupportSelected) {
				p1SupportSelected = false;
				p1Support.Unselected();
				p1Sound.setBuffer(cursorBackSFX);
				p1Sound.play();
			}
			return true;
		}
	}
	else
		p1CancelHeld = false;

	return true;
}

bool VsCharSelect::CheckP2CharInputs() {
	int yAxis, xAxis;
	bool selectionChanged = false;

	if (!p2SupportSelected) {
		xAxis = p2Controls->GetHorizontalAxis();
		if (0 != xAxis && xAxis != lastP2Horiz) {
			p2Sound.setBuffer(cursorMoveSFX);
			p2Sound.play();
			p2CursorPosition.x += 1 * xAxis;
			selectionChanged = true;
		}
		lastP2Horiz = xAxis;

		yAxis = p2Controls->GetVerticalAxis();
		if (p2MainSelected && 0 != yAxis && yAxis != lastP2Vert) {
			p2Sound.setBuffer(cursorMoveSFX);
			p2Sound.play();
			p2CursorPosition.y += 1 * yAxis;
			selectionChanged = true;
		}
		lastP2Vert = yAxis;
	}

	if (selectionChanged)
		UpdateP2UI();

	if (p2Controls->isActionPressed(Controls::Actions::Light)) {
		if (!p2ConfirmHeld) {
			p2ConfirmHeld = true;
			if (!p2MainSelected) {
				if (1 == p2CursorPosition.x) {
					p2CursorPosition.x = GetRandomPlayable(2);
					UpdateP2UI();
				}
				p2Sound.setBuffer(cursorSelectSFX);
				p2Sound.play();
				p2MainSelected = true;
				//p2Support = p2Main;
				p2Main.Selected();
				p2Support = playableFighters[1];
				p2CursorPosition.x = 1;
				UpdateP2UI();
			}
			else if (!p2SupportSelected) {
				if (1 == p2CursorPosition.x) {
					if (1 == p2CursorPosition.y)
						p2CursorPosition.x = GetRandomSupport(2);
					else
						p2CursorPosition.x = GetRandomPlayable(2);

					UpdateP2UI();
				}
				p2Sound.setBuffer(cursorSelectSFX);
				p2Sound.play();
				p2SupportSelected = true;
				p2Support.Selected();
			}
			return true;
		}
	}
	else
		p2ConfirmHeld = false;

	if (p2Controls->isActionPressed(Controls::Actions::Heavy)) {
		if (!p2CancelHeld) {
			p2CancelHeld = true;
			if (p2SupportSelected) {
				p2SupportSelected = false;
				p2Support.Unselected();
				p2Sound.setBuffer(cursorBackSFX);
				p2Sound.play();
			}
			else if (p2MainSelected) {
				p2MainSelected = false;
				p2Main.Unselected();
				p2CursorPosition.y = 0;
				UpdateP2UI();
				p2Sound.setBuffer(cursorBackSFX);
				p2Sound.play();
			}
			else {
				charSelectMusic.stop();
				//charSelectSound.stop();
				p1Sound.stop();
				p2Sound.stop();
				ApplicationData::sceneManager->SetCurrentScene(TITLE_SCREEN);
				return false;
			}
			return true;
		}
	}
	else
		p2CancelHeld = false;

	return true;
}

bool VsCharSelect::CheckP2StageInputs() {
	int yAxis, xAxis;

	xAxis = p2Controls->GetHorizontalAxis();
	if (0 != xAxis && xAxis != lastP2Horiz) {
		currentStageOption += 1 * xAxis;
		if (0 > currentStageOption)
			currentStageOption = NUM_OF_STAGES - 1;
		else if ((NUM_OF_STAGES - 1) < currentStageOption)
			currentStageOption = 0;
		currentStageOptionSprite.setTexture(stageSampleTextures[currentStageOption]);
		p2Sound.setBuffer(cursorMoveSFX);
		p2Sound.play();
	}
	lastP2Horiz = xAxis;

	if (p2Controls->isActionPressed(Controls::Actions::Light)) {
		if (!p2ConfirmHeld) {
			p2ConfirmHeld = true;
			p2Sound.setBuffer(cursorSelectSFX);
			p2Sound.play();
			OnToTheFight();
			return false;
		}
	}
	else
		p2ConfirmHeld = false;

	if (p2Controls->isActionPressed(Controls::Actions::Heavy)) {
		if (!p2CancelHeld) {
			p2CancelHeld = true;
			if (p2SupportSelected) {
				p2SupportSelected = false;
				p2Support.Unselected();
				p2Sound.setBuffer(cursorBackSFX);
				p2Sound.play();
			}
			return true;
		}
	}
	else
		p2CancelHeld = false;

	return true;
}

void VsCharSelect::Draw(sf::RenderWindow* window) {
	if (sceneDone)
		return; 

	window->setView(camera);

	sf::RectangleShape background;
	background.setSize(camera.getSize());
	background.setOrigin(background.getSize().x * 0.5f, background.getSize().y * 0.5f);
	background.setPosition(camera.getCenter());
	background.setFillColor(sf::Color::Magenta);

	window->draw(background);

	window->draw(backgroundSprite);

	if (p1SupportSelected && p2SupportSelected) {
		window->draw(currentStageOptionSprite);
		window->draw(stageTitleSprite);
		window->draw(leftArrowSprite);
		window->draw(rightArrowSprite);
	}
	else {
		for (int i = 0; i < 3; i++) {
			playableFighters[i].DrawPortrait(window);
			if (p1MainSelected || p2MainSelected) supportFighters[i].DrawPortrait(window);
		}

		
		if(1 != p2CursorPosition.x)
			window->draw(p2CursorSprite);
		else {
			if (1 == p2CursorPosition.y) {
				p2Rand2CursorSprite.setPosition(p2CursorSprite.getPosition());
				window->draw(p2Rand2CursorSprite);
			}
			else {
				p2Rand1CursorSprite.setPosition(p2CursorSprite.getPosition());
				window->draw(p2Rand1CursorSprite);
			}
		}

		if (1 != p1CursorPosition.x)
			window->draw(p1CursorSprite);
		else {
			if (1 == p1CursorPosition.y) {
				p1Rand2CursorSprite.setPosition(p1CursorSprite.getPosition());
				window->draw(p1Rand2CursorSprite);
			}
			else {
				p1Rand1CursorSprite.setPosition(p1CursorSprite.getPosition());
				window->draw(p1Rand1CursorSprite);
			}
		}

		window->draw(charTitleSprite);
		if (p1MainSelected || p2MainSelected) window->draw(assistTextSprite);
	}

	p1Main.DrawCurrentAnimation(window);
	if (p1MainSelected) p1Support.DrawCurrentAnimation(window);
	p2Main.DrawCurrentAnimation(window);
	if (p2MainSelected) p2Support.DrawCurrentAnimation(window);
}

void VsCharSelect::OnToTheFight() {
	p1MainName = p1Main.GetName();
	p1MainAltColor = p1Main.GetAltColorUsage();
	p1SupportName = p1Support.GetName();
	p1SupportAltColor = p1Support.GetAltColorUsage();
	p2MainName = p2Main.GetName();
	p2MainAltColor = p2Main.GetAltColorUsage();
	p2SupportName = p2Support.GetName();
	p2SupportAltColor = p2Support.GetAltColorUsage();
	selectedStage = GetAllStageStrings()[currentStageOption];
	
	charSelectMusic.stop();
	p1Sound.stop();
	p2Sound.stop();
	
	sceneDone = true;
	ApplicationData::sceneManager->SetCurrentScene(LOCAL_VERSUS);
	return;
}

int VsCharSelect::GetRandomPlayable(int playerNo) {
	string mainName = (2 == playerNo) ? p2Main.GetName() : p1Main.GetName();
	srand(time(NULL));
	int random = rand() % 3;
	if (1 == random)
		random--;

	if (playableFighters[random].GetName() == mainName) {
		random--;
		if (1 == random)
			random--;
	}
	return random;
}

int VsCharSelect::GetRandomSupport(int playerNo) {
	string mainName = (2 == playerNo) ? p2Main.GetName() : p1Main.GetName();
	srand(time(NULL));
	int random = rand() % 3;
	if (1 == random)
		random--;

	if (supportFighters[random].GetName() == mainName) {
		random--;
		if (1 == random)
			random--;
	}
	return random;
}
void VsCharSelect::UpdateP1UI() {
	if (0 > p1CursorPosition.x)
		p1CursorPosition.x = 2;
	else if (2 < p1CursorPosition.x)
		p1CursorPosition.x = 0;

	if (0 > p1CursorPosition.y)
		p1CursorPosition.y = 1;
	else if (1 < p1CursorPosition.y || !p1MainSelected)
		p1CursorPosition.y = 0;

	if (1 == p1CursorPosition.y) {
		p1CursorSprite.setPosition(supportFighters[p1CursorPosition.x].GetPortraitPosition());
		p1CursorSprite.setScale((0 < p1CursorPosition.x) ? -1.f : 1.f, 1.f);
		if (!p1MainSelected) {
			p1Main = supportFighters[p1CursorPosition.x];
			if ((p1Main.GetName() == p2Main.GetName() && 1 == p2Main.GetAltColorUsage())
				|| ((p2MainSelected) && p1Main.GetName() == p2Support.GetName() && 1 == p2Support.GetAltColorUsage()))
				p1Main.UseAltColor();
		}
		else if (!p1SupportSelected) {
			p1Support = supportFighters[p1CursorPosition.x];
			if ((p1Support.GetName() == p2Main.GetName() && 1 == p2Main.GetAltColorUsage())
				|| ((p2MainSelected) && p1Support.GetName() == p2Support.GetName() && 1 == p2Support.GetAltColorUsage())
				|| (p1Support.GetName() == p2Main.GetName() && 1 == p2Main.GetAltColorUsage()))
				p1Support.UseAltColor();
		}
	}
	else {
		p1CursorSprite.setPosition(playableFighters[p1CursorPosition.x].GetPortraitPosition());
		p1CursorSprite.setScale((0 < p1CursorPosition.x) ? -1.f : 1.f, 1.f);
		if (!p1MainSelected) {
			p1Main = playableFighters[p1CursorPosition.x];
			if ((p1Main.GetName() == p2Main.GetName() && 1 == p2Main.GetAltColorUsage())
				|| ((p2MainSelected) && p1Main.GetName() == p2Support.GetName() && 1 == p2Support.GetAltColorUsage()))
				p1Main.UseAltColor();
		}
		else if (!p1SupportSelected) {
			p1Support = playableFighters[p1CursorPosition.x];
			if ((p1Support.GetName() == p2Main.GetName() && 1 == p2Main.GetAltColorUsage())
				|| ((p2MainSelected) && p1Support.GetName() == p2Support.GetName() && 1 == p2Support.GetAltColorUsage())
				|| (p1Support.GetName() == p2Main.GetName() && 1 == p2Main.GetAltColorUsage()))
				p1Support.UseAltColor();
		}
	}

	if ((p1MainSelected) && p1Support.GetName() == p1Main.GetName()) {
		p1CursorPosition.x = 1;
		UpdateP1UI();
	}
}

void VsCharSelect::UpdateP2UI() {
	if (0 > p2CursorPosition.x)
		p2CursorPosition.x = 2;
	else if (2 < p2CursorPosition.x)
		p2CursorPosition.x = 0;

	if (0 > p2CursorPosition.y)
		p2CursorPosition.y = 1;
	else if (1 < p2CursorPosition.y || !p2MainSelected)
		p2CursorPosition.y = 0;

	if (1 == p2CursorPosition.y) {
		p2CursorSprite.setPosition(supportFighters[p2CursorPosition.x].GetPortraitPosition());
		p2CursorSprite.setScale((0 < p2CursorPosition.x) ? -1.f : 1.f, 1.f);
		if (!p2MainSelected) {
			p2Main = supportFighters[p2CursorPosition.x];
			if ((p2Main.GetName() == p1Main.GetName() && 1 == p1Main.GetAltColorUsage())
				|| ((p1MainSelected) && p2Main.GetName() == p1Support.GetName() && 1 == p1Support.GetAltColorUsage()))
				p2Main.UseAltColor();
		}
		else if (!p2SupportSelected) {
			p2Support = supportFighters[p2CursorPosition.x];
			if ((p2Support.GetName() == p1Main.GetName() && 1 == p1Main.GetAltColorUsage())
				|| ((p1MainSelected) && p2Support.GetName() == p1Support.GetName() && 1 == p1Support.GetAltColorUsage())
				|| (p2Support.GetName() == p2Main.GetName() && 1 == p1Main.GetAltColorUsage()))
				p2Support.UseAltColor();
		}
	}
	else {
		p2CursorSprite.setPosition(playableFighters[p2CursorPosition.x].GetPortraitPosition());
		p2CursorSprite.setScale((0 < p2CursorPosition.x) ? -1.f : 1.f, 1.f);
		if (!p2MainSelected) {
			p2Main = playableFighters[p2CursorPosition.x];
			if ((p2Main.GetName() == p1Main.GetName() && 1 == p1Main.GetAltColorUsage())
				|| ((p1MainSelected) && p2Main.GetName() == p1Support.GetName() && 1 == p1Support.GetAltColorUsage()))
				p2Main.UseAltColor();
		}
		else if (!p2SupportSelected) {
			p2Support = playableFighters[p2CursorPosition.x];
			if ((p2Support.GetName() == p1Main.GetName() && 1 == p1Main.GetAltColorUsage())
				|| ((p1MainSelected) && p2Support.GetName() == p1Support.GetName() && 1 == p1Support.GetAltColorUsage())
				|| (p2Support.GetName() == p2Main.GetName() && 1 == p1Main.GetAltColorUsage()))
				p2Support.UseAltColor();
		}
	}

	if ((p2MainSelected) && p2Support.GetName() == p2Main.GetName()) {
		p2CursorPosition.x = 1;
		UpdateP2UI();
	}
}
