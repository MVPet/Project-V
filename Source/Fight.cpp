#include "Fight.h"
#include "FighterStrings.h"
#include "StageStrings.h"
#include "ApplicationData.h"
#include "Utilities.h"
#include "Fighter.h"

#include <stdio.h>
#include <iostream>

Stage* Fight::stage = nullptr;
Player* Fight::player1 = nullptr;
Player* Fight::player2 = nullptr;
sf::View Fight::camera;
float Fight::cameraJumpBound;
float Fight::cameraBaseY;
Animation* Fight::lightSpark = nullptr;
Animation* Fight::mediumSpark = nullptr;
Animation* Fight::heavySpark = nullptr;
Animation* Fight::guardSpark = nullptr;
Animation* Fight::hyperSpark = nullptr;
std::vector<Animation> Fight::allHitSparks;
bool Fight::doingHyperSpark = false;
bool Fight::p1HyperSwap = false;
bool Fight::p2HyperSwap = false;
bool Fight::cameraLock = false;
bool Fight::isFocusing = false;
int Fight::focusOnPlayer = -1;
bool Fight::isPaused = false;
PauseMenu* Fight::pauseMenu = nullptr;
int Fight::endCountdown = 0;
bool Fight::showKO = false;
bool Fight::disableWinCondition = false;
sf::Sound Fight::announcerSound;
sf::Music Fight::bgMusic;
sf::SoundBuffer Fight::lightSFX;
sf::SoundBuffer Fight::mediumSFX;
sf::SoundBuffer Fight::heavySFX;
sf::SoundBuffer Fight::guardSFX;
sf::Sound Fight::hitSound;
sf::SoundBuffer Fight::koSFX;
sf::SoundBuffer Fight::hyperSFX;
sf::SoundBuffer Fight::readySFX;
sf::SoundBuffer Fight::fightSFX;
bool Fight::p1IntroDone = false;
bool Fight::p2IntroDone = false;
bool Fight::allIntrosDone = false;

extern string p1MainName;
extern int p1MainAltColor;
extern string p1SupportName;
extern int p1SupportAltColor;
extern string p2MainName;
extern int p2MainAltColor;
extern string p2SupportName;
extern int p2SupportAltColor;
extern string selectedStage;
extern int x;

// PUBLIC FUNCTIONS

void Fight::RestoreDefaults() {
	stage = nullptr;
	player1 = nullptr;
	player2 = nullptr;
	lightSpark = nullptr;
	mediumSpark = nullptr;
	heavySpark = nullptr;
	guardSpark = nullptr;
	hyperSpark = nullptr;
	doingHyperSpark = false;
	p1HyperSwap = false;
	p2HyperSwap = false;
	cameraLock = false;
	isFocusing = false;
	focusOnPlayer = -1;
	isPaused = false;
	pauseMenu = nullptr;
	endCountdown = 0;
	showKO = false;
	disableWinCondition = false;
	p1IntroDone = false;
	p2IntroDone = false;
	allIntrosDone = false;
}

Fight::Fight() {
	RestoreDefaults();

	player1 = new Player(1, p1MainName, p1SupportName);
	player2 = new Player(2, p2MainName, p2SupportName);

	stage = new Stage();
	stage->Load(selectedStage);

	player1->SetPosition(stage->GetPlayer1Spawn());
	player2->SetPosition(stage->GetPlayer2Spawn());

	player1->SetMainEnemy(player2->GetMain());
	player2->SetMainEnemy(player1->GetMain());

	player1->SetColors(p1MainAltColor, p1SupportAltColor);
	player2->SetColors(p2MainAltColor, p2SupportAltColor);

	LoadHitSparks();

	hyperTexture = new sf::Texture;
	if (!hyperTexture->loadFromFile("Textures/Misc/HyperBackground.png"))
		std::cout << "CANNOT LOAD HYPER BACKGROUND" << std::endl;

	if (!readyTextTexture.loadFromFile("Textures/Misc/Fight_HUD/ReadyText.png"))
		std::cout << "CANNOT LOAD READY TEXT" << std::endl;
	readyTextSprite.setTexture(readyTextTexture);
	readyTextSprite.setOrigin(GetTextureCenter(&readyTextTexture));

	if (!fightTextTexture.loadFromFile("Textures/Misc/Fight_HUD/FightText.png"))
		std::cout << "CANNOT LOAD READY TEXT" << std::endl;
	fightTextSprite.setTexture(fightTextTexture);
	fightTextSprite.setOrigin(GetTextureCenter(&fightTextTexture));

	healthBarBackground = new sf::Texture;
	if (!healthBarBackground->loadFromFile("Textures/Misc/Fight_HUD/BackgroundBar.png"))
		std::cout << "CANNOT LOAD HEALTH BAR BACKGROUND" << std::endl;
	healthBarBackgroundSprite.setTexture(*healthBarBackground);
	healthBarBackgroundSpriteP1Assist.setTexture(*healthBarBackground);
	healthBarBackgroundSpriteP1Assist.setTextureRect(sf::IntRect(0.f, 0.f, healthBarBackground->getSize().x, healthBarBackground->getSize().y * 0.5f));
	healthBarBackgroundSpriteP2.setTexture(*healthBarBackground);
	healthBarBackgroundSpriteP2Assist.setTexture(*healthBarBackground);
	healthBarBackgroundSpriteP2Assist.setTextureRect(sf::IntRect(0.f, 0.f, healthBarBackground->getSize().x, healthBarBackground->getSize().y * 0.5f));
	healthBarBackgroundSprite.setScale(0.35f, 0.35f);
	healthBarBackgroundSpriteP2.setScale(-0.35f, 0.35f);
	healthBarBackgroundSpriteP1Assist.scale(sf::Vector2f(0.35f, 0.35f));
	healthBarBackgroundSpriteP2Assist.scale(sf::Vector2f(-0.35f, 0.35f));

	healthBarForeground = new sf::Texture;
	if (!healthBarForeground->loadFromFile("Textures/Misc/Fight_HUD/HealthBar.png"))
		std::cout << "CANNOT LOAD HEALTH BAR FOREGROUND" << std::endl;
	healthBarForegroundSprite.setTexture(*healthBarForeground);
	healthBarForegroundSpriteP1Assist.setTexture(*healthBarForeground);
	healthBarForegroundSpriteP2.setTexture(*healthBarForeground);
	healthBarForegroundSpriteP2Assist.setTexture(*healthBarForeground);
	healthBarForegroundSprite.setScale(0.35f, 0.35f);
	healthBarForegroundSpriteP2.setScale(-0.35f, 0.35f);
	healthBarForegroundSpriteP1Assist.scale(sf::Vector2f(0.35f, 0.35f));
	healthBarForegroundSpriteP2Assist.scale(sf::Vector2f(-0.35f, 0.35f));

	redBarForeground = new sf::Texture;
	if (!redBarForeground->loadFromFile("Textures/Misc/Fight_HUD/RedBar.png"))
		std::cout << "CANNOT LOAD RED BAR FOREGROUND" << std::endl;
	redBarForegroundSprite.setTexture(*redBarForeground);
	redBarForegroundSpriteP1Assist.setTexture(*redBarForeground);
	redBarForegroundSpriteP2.setTexture(*redBarForeground);
	redBarForegroundSpriteP2Assist.setTexture(*redBarForeground);
	redBarForegroundSprite.setScale(0.35f, 0.35f);
	redBarForegroundSpriteP2.setScale(-0.35f, 0.35f);
	redBarForegroundSpriteP1Assist.scale(sf::Vector2f(0.35f, 0.35f));
	redBarForegroundSpriteP2Assist.scale(sf::Vector2f(-0.35f, 0.35f));

	specialBarBackground = new sf::Texture;
	if (!specialBarBackground->loadFromFile("Textures/Misc/Fight_HUD/SpecialBackground.png"))
		std::cout << "CANNOT LOAD SPECIAL BAR BACKGROUND" << std::endl;
	specialBarBackgroundSprite.setTexture(*specialBarBackground);
	specialBarBackgroundSprite.scale(sf::Vector2f(0.5f, 0.5f));
	specialBarBackgroundSpriteP2.setTexture(*specialBarBackground);
	specialBarBackgroundSpriteP2.scale(sf::Vector2f(-0.5f, 0.5f));

	specialBarForeground = new sf::Texture;
	if (!specialBarForeground->loadFromFile("Textures/Misc/Fight_HUD/SpecialBarForeground.png"))
		std::cout << "CANNOT LOAD SPECIAL BAR FOREGROUND" << std::endl;
	specialBarForegroundSprite.setTexture(*specialBarForeground);
	specialBarForegroundSprite.scale(sf::Vector2f(0.5f, 0.5f));
	specialBarForegroundSpriteP2.setTexture(*specialBarForeground);
	specialBarForegroundSpriteP2.scale(sf::Vector2f(-0.5f, 0.5f));

	if (!font.loadFromFile("Fonts/arial.ttf"))
		std::cout << "CANNOT LOAD FONT" << std::endl;

	if (!hitsTexture.loadFromFile("Textures/Misc/Fight_HUD/Hits.png"))
		std::cout << "CANNOT LOAD BLACK BACKGROUND" << std::endl;
	hitsSpriteP1.setTexture(hitsTexture);
	hitsSpriteP2.setTexture(hitsTexture);

	if (!p1WinTexture.loadFromFile("Textures/Misc/Fight_HUD/P1Win.png"))
		std::cout << "CANNOT LOAD BLACK BACKGROUND" << std::endl;
	if (!p2WinTexture.loadFromFile("Textures/Misc/Fight_HUD/P2Win.png"))
		std::cout << "CANNOT LOAD BLACK BACKGROUND" << std::endl;
	if (!tieTesture.loadFromFile("Textures/Misc/Fight_HUD/Draw.png"))
		std::cout << "CANNOT LOAD BLACK BACKGROUND" << std::endl;
	winnerSprite.setOrigin(GetTextureCenter(&p2WinTexture));
	winnerSprite.setPosition(camera.getCenter().x, camera.getCenter().y - 60.f);

	if (!KOTextTexure.loadFromFile("Textures/Misc/Fight_HUD/KOText.png"))
		std::cout << "CANNOT LOAD BLACK BACKGROUND" << std::endl;
	KOTextSprite.setTexture(KOTextTexure);
	KOTextSprite.setOrigin(GetTextureCenter(&KOTextTexure));

	for (int i = 0; i < 10; i++) {
		if (!numberTextures[i].loadFromFile("Textures/Misc/Fight_HUD/" + to_string(i) + ".png"))
			std::cout << "CANNOT LOAD BLACK BACKGROUND" << std::endl;
	}

	camera.setSize(1280, 720);
	camera.zoom(0.35f);
	cameraBaseY = stage->GetStageBottom() - (camera.getSize().y * 0.5f);
	camera.setCenter(stage->GetCenter().x, cameraBaseY);
	cameraJumpBound = camera.getCenter().y - camera.getSize().y * 0.45f;

	pauseMenu = new PauseMenu();

	if (!bgMusic.openFromFile("Music/Ryu.wav"))
		printf("CANNOT LOAD MUSIC: CharSelect\n");
	bgMusic.play();
	bgMusic.setLoop(true);

	if (!readySFX.loadFromFile("SFX/readySFX1.wav"))
		std::cout << "CANNOT LOAD TITLE SFX" << std::endl;
	if (!fightSFX.loadFromFile("SFX/fightSFX.wav"))
		std::cout << "CANNOT LOAD FIGHT SFX" << std::endl;
	if (!lightSFX.loadFromFile("SFX/lightSFX.wav"))
		std::cout << "CANNOT LOAD lightSFX SFX" << std::endl;
	if (!mediumSFX.loadFromFile("SFX/mediumSFX.wav"))
		std::cout << "CANNOT LOAD mediumSFX SFX" << std::endl;
	if (!heavySFX.loadFromFile("SFX/heavySFX.wav"))
		std::cout << "CANNOT LOAD heavySFX SFX" << std::endl;
	if (!guardSFX.loadFromFile("SFX/guardSFX.wav"))
		std::cout << "CANNOT LOAD guardSFX SFX" << std::endl;
	if (!koSFX.loadFromFile("SFX/koSFX.wav"))
		std::cout << "CANNOT LOAD koSFX SFX" << std::endl;
	if (!hyperSFX.loadFromFile("SFX/hyperSFX.wav"))
		std::cout << "CANNOT LOAD hyperSFX SFX" << std::endl;

	hitSound.setVolume(75);
}

Fight::~Fight() {
	delete player1;
	delete player2;
	delete stage;
	delete pauseMenu;
}

void Fight::UpdateEvent(sf::Event event) {
	if (!isPaused && !doingHyperSpark) {
		player1->UpdateEvent(event);
		player2->UpdateEvent(event);
	}
}

void Fight::UpdateHitSparks() {
	if (!allHitSparks.empty()) {
		for (int i = 0; i < allHitSparks.size(); i++) {
			allHitSparks[i].Update();

			if (allHitSparks[i].IsDone()) {
				if (allHitSparks[i].GetName() == "Hyper") {
					doingHyperSpark = false;
				}
				allHitSparks.erase(allHitSparks.begin() + i);
			}
		}
	}
}

void Fight::Update() {
	if (showPostGameMenu) {
		postGameMenu.Update(player1->GetControls(), player2->GetControls());
		return;
	}

	if (!isPaused && allIntrosDone && readyIntro) {
		readyIntroTimer--;
		if (0 >= readyIntroTimer) {
			readyIntro = false;
			player1->SetReadyIntro(readyIntro);
			player2->SetReadyIntro(readyIntro);
			announcerSound.setBuffer(fightSFX);
			announcerSound.play();
		}
	}

	player1->SetMainEnemy(player2->GetMain());
	player2->SetMainEnemy(player1->GetMain());

	if (!isPaused) {
		if (!doingHyperSpark) {
			if (allIntrosDone) {
				if (!p2HyperSwap) player1->CheckInput();
				if (!p1HyperSwap) player2->CheckInput();
			}

			if (!p2HyperSwap) player1->CheckEnemyCollision(player2->GetMain());
			if (!p2HyperSwap) player1->CheckEnemyCollision(player2->GetSupport());
			if (!p1HyperSwap) player2->CheckEnemyCollision(player1->GetMain());
			if (!p1HyperSwap) player2->CheckEnemyCollision(player1->GetSupport());
			if (!p2HyperSwap) player1->CheckBoundaryCollision();
			if (!p1HyperSwap) player2->CheckBoundaryCollision();

			if (!p2HyperSwap) player1->Update(player2->GetMain());
			if (!p1HyperSwap) player2->Update(player1->GetMain());

			if (!cameraLock) UpdateCamera();
			stage->Update(camera);
			UpdateHUD();
		}

		UpdateHitSparks();
	}
	else
		isPaused = pauseMenu->Update(player1->GetControls(), player2->GetControls());

	CheckForVictory();

	if (!isPaused && !readyIntro && !fightIsOver && 0 < timeLimit) {
		timeLimit--;
		fightTextTimer--;
	}

	if (0 < endCountdown) {
		endCountdown--;
		if (0 >= endCountdown) {
			showPostGameMenu = true;
			postGameMenu.SetPosition(camera);
		}
	}
}

void Fight::CheckForVictory() {
	if (disableWinCondition)
		return;

	if (!fightIsOver) {
		if (player1->CheckFightersHealth() && player2->CheckFightersHealth()) {
			player1->FightIsOver(0);
			player2->FightIsOver(0);
			winnerSprite.setTexture(tieTesture);
			winnerSprite.setOrigin(GetTextureCenter(&p2WinTexture));
			winnerSprite.setPosition(camera.getCenter().x, camera.getCenter().y - 55.f);
			fightIsOver = true;
		}
		else if (!player1->CheckFightersHealth() && player2->CheckFightersHealth()) {
			player1->FightIsOver(1);
			player2->FightIsOver(1);
			winnerSprite.setTexture(p1WinTexture);
			winnerSprite.setOrigin(GetTextureCenter(&p2WinTexture));
			winnerSprite.setPosition(camera.getCenter().x, camera.getCenter().y - 55.f);
			fightIsOver = true;
		}
		else if (player1->CheckFightersHealth() && !player2->CheckFightersHealth()) {
			player1->FightIsOver(2);
			player2->FightIsOver(2);
			winnerSprite.setTexture(p2WinTexture);
			winnerSprite.setOrigin(GetTextureCenter(&p2WinTexture));
			winnerSprite.setPosition(camera.getCenter().x, camera.getCenter().y - 55.f);
			fightIsOver = true;
		}
		else if ((0 >= timeLimit)) {
			fightIsOver = true;
			if (player1->GetTotalRemainingHealth() > player2->GetTotalRemainingHealth()) {
				player1->FightIsOver(1);
				player2->FightIsOver(1);
				winnerSprite.setTexture(p1WinTexture);
				winnerSprite.setOrigin(GetTextureCenter(&p2WinTexture));
				winnerSprite.setPosition(camera.getCenter().x, camera.getCenter().y - 55.f);
			}
			else if (player2->GetTotalRemainingHealth() > player1->GetTotalRemainingHealth()) {
				player1->FightIsOver(2);
				player2->FightIsOver(2);
				winnerSprite.setTexture(p2WinTexture);
				winnerSprite.setOrigin(GetTextureCenter(&p2WinTexture));
				winnerSprite.setPosition(camera.getCenter().x, camera.getCenter().y - 55.f);
			}
			else {
				player1->FightIsOver(0);
				player2->FightIsOver(0);
				winnerSprite.setTexture(tieTesture);
				winnerSprite.setOrigin(GetTextureCenter(&p2WinTexture));
				winnerSprite.setPosition(camera.getCenter().x, camera.getCenter().y - 55.f);
			}
		}
	}
}

void Fight::DrawHitSparks(sf::RenderWindow* window) {
	if (!allHitSparks.empty()) {
		for (int i = 0; i < allHitSparks.size(); i++) {
			allHitSparks[i].Draw(window, sf::Color::White);
		}
	}
}

void Fight::DrawCombo(sf::RenderWindow* window) {

	// P1
	if (1 < player1->GetCurrentCombo()) {
		if (0 != player1->GetCurrentCombo() / 10) {
			comboDigit1P1.setTexture(numberTextures[player1->GetCurrentCombo() / 10]);
			comboDigit1P1.setPosition(camera.getCenter().x - 210.f, camera.getCenter().y - 60.f);
			comboDigit1P1.setScale(0.35f, 0.35f);
			window->draw(comboDigit1P1);
		}

		comboDigit2P1.setTexture(numberTextures[player1->GetCurrentCombo() % 10]);
		comboDigit2P1.setPosition(camera.getCenter().x - 193.f, camera.getCenter().y - 60.f);
		comboDigit2P1.setScale(0.35f, 0.35f);

		hitsSpriteP1.setPosition(camera.getCenter().x - 173.f, camera.getCenter().y - 60.f);
		hitsSpriteP1.setScale(0.35f, 0.35f);
		window->draw(comboDigit2P1);
		window->draw(hitsSpriteP1);
	}

	// P2
	if (1 < player2->GetCurrentCombo()) {
		if (0 != player2->GetCurrentCombo() / 10) {
			comboDigit1P2.setTexture(numberTextures[player2->GetCurrentCombo() / 10]);
			comboDigit1P2.setPosition(camera.getCenter().x + 135.f, camera.getCenter().y - 60.f);
			comboDigit1P2.setScale(0.35f, 0.35f);
			window->draw(comboDigit1P2);
		}

		comboDigit2P2.setTexture(numberTextures[player2->GetCurrentCombo() % 10]);
		comboDigit2P2.setPosition(camera.getCenter().x + 152.f, camera.getCenter().y - 60.f);
		comboDigit2P2.setScale(0.35f, 0.35f);

		hitsSpriteP2.setPosition(camera.getCenter().x + 172.f, camera.getCenter().y - 60.f);
		hitsSpriteP2.setScale(0.35f, 0.35f);

		window->draw(comboDigit2P2);
		window->draw(hitsSpriteP2);
	}
}

void Fight::DrawSpecialBarNumbers(sf::RenderWindow* window) {

	int numOfSpecialBar = player1->GetMain()->GetNumberOfSpecialBars();
	specialValueP1Sprite.setTexture(numberTextures[numOfSpecialBar]);
	specialValueP1Sprite.setPosition(specialBarBackgroundSprite.getPosition().x + 5.f, specialBarBackgroundSprite.getPosition().y + 2.f);
	specialValueP1Sprite.setScale(0.35f, 0.35f);

	window->draw(specialValueP1Sprite);

	numOfSpecialBar = player2->GetMain()->GetNumberOfSpecialBars();
	specialValueP2Sprite.setTexture(numberTextures[numOfSpecialBar]);
	specialValueP2Sprite.setPosition(specialBarBackgroundSpriteP2.getPosition().x - 22.f, specialBarBackgroundSpriteP2.getPosition().y + 2.f);
	specialValueP2Sprite.setScale(0.35f, 0.35f);

	window->draw(specialValueP2Sprite);
}

void Fight::Draw(sf::RenderWindow* window) {

	window->setView(camera);

	stage->DrawBackground(window);

	if (doingHyperSpark || p1HyperSwap || p2HyperSwap) {
		sf::RectangleShape hyperBackground;
		hyperBackground.setSize(camera.getSize());
		hyperBackground.setOrigin(hyperBackground.getSize().x * 0.5f, hyperBackground.getSize().y * 0.5f);
		hyperBackground.setPosition(camera.getCenter());
		hyperBackground.setTexture(hyperTexture);

		window->draw(hyperBackground);
	}

	window->draw(*player1->GetMain()->getBattlePortrait());
	window->draw(healthBarBackgroundSprite);
	window->draw(redBarForegroundSprite);
	window->draw(healthBarForegroundSprite);

	window->draw(*player1->GetSupport()->getSupportPortrait());
	if (player1->GetSupport()->isPlayable) {
		window->draw(healthBarBackgroundSpriteP1Assist);
		window->draw(redBarForegroundSpriteP1Assist);
		window->draw(healthBarForegroundSpriteP1Assist);
	}

	window->draw(*player2->GetMain()->getBattlePortrait());
	window->draw(healthBarBackgroundSpriteP2);
	window->draw(redBarForegroundSpriteP2);
	window->draw(healthBarForegroundSpriteP2);

	window->draw(*player2->GetSupport()->getSupportPortrait());
	if (player2->GetSupport()->isPlayable) {
		window->draw(healthBarBackgroundSpriteP2Assist);
		window->draw(redBarForegroundSpriteP2Assist);
		window->draw(healthBarForegroundSpriteP2Assist);
	}

	if (player2->GetSupport()->GetKOed()) player2->DrawSupport(window);
	if (player1->GetSupport()->GetKOed()) player1->DrawSupport(window);

	if (player1->GetDrawFirst() || !player2->GetDrawFirst()) {
		player2->DrawMain(window);
		player1->DrawMain(window);
	}
	else {
		player1->DrawMain(window);
		player2->DrawMain(window);
	}

	if (!player2->GetSupport()->GetKOed()) player2->DrawSupport(window);
	if (!player1->GetSupport()->GetKOed()) player1->DrawSupport(window);

	DrawHitSparks(window);

	stage->DrawForeground(window);

	window->draw(specialBarBackgroundSprite);
	window->draw(specialBarForegroundSprite);
	window->draw(specialBarBackgroundSpriteP2);
	window->draw(specialBarForegroundSpriteP2);
	DrawCombo(window);
	DrawSpecialBarNumbers(window);
	if (!disableWinCondition) DrawGameTimer(window);

	if (allIntrosDone) {
		if (readyIntro)
			window->draw(readyTextSprite);
		else {
			if (0 < fightTextTimer)
				window->draw(fightTextSprite);
		}
	}

	if (showKO && 1 != ApplicationData::GetGameSpeed())
		window->draw(KOTextSprite);

	if (fightIsOver) {
		if (0 < endCountdown)
			window->draw(winnerSprite);
	}

	if (isPaused) pauseMenu->Draw(window);

	if (showPostGameMenu) postGameMenu.Draw(window);
}

// PRIVATE FUNCTIONS
void Fight::UpdateCamera() {
	sf::Vector2f player1Position = player1->GetPosition();
	sf::Vector2f player2Position = player2->GetPosition();

	float cameraNewX;
	float cameraNewY;

	float minTopBound;
	float player1TopBound = player1->GetMain()->GetAnimationManager().GetCurrentAnimation()->GetBoundBox().top;
	float player2TopBound = player2->GetMain()->GetAnimationManager().GetCurrentAnimation()->GetBoundBox().top;

	if (isFocusing) {
		sf::Vector2f focusPosition = (2 == focusOnPlayer) ? player2->GetPosition() : player1->GetPosition();
		cameraNewX = (player1Position.x + player2Position.x) / 2.f;
		cameraNewY = focusPosition.y;
		minTopBound = (2 == focusOnPlayer) ? player2TopBound : player1TopBound;
	}
	else {
		cameraNewX = (player1Position.x + player2Position.x) / 2.f;
		cameraNewY = camera.getCenter().y;
		minTopBound = min(player1TopBound, player2TopBound); // Has an issue where a sprite has no bound box, will tilt camera too high up
	}

	float cameraLeft = cameraNewX - camera.getSize().x * 0.5f;
	float cameraRight = cameraNewX + camera.getSize().x * 0.5f;
	float cameraBottom = camera.getCenter().y + (camera.getSize().y * 0.5f * 0.35f);
	float stageLeft = stage->GetLeftBound();
	float stageRight = stage->GetRightBound();
	float stageBottom = stage->GetStageBottom();

	if (minTopBound < cameraJumpBound) {
		cameraNewY = cameraBaseY - (cameraJumpBound - minTopBound);
	}
	else {
		cameraNewY = cameraBaseY;
	}

	// Left Bound
	if (cameraLeft < stageLeft)
		cameraNewX = stageLeft + camera.getSize().x * 0.5f;
	// Right Bound
	else if (cameraRight > stageRight)
		cameraNewX = stageRight - camera.getSize().x * 0.5f;

	camera.setCenter(cameraNewX, cameraNewY); // Should set in the stage where the camera should be
}

void Fight::UpdateHUD() {
	sf::Vector2f cameraCenter = camera.getCenter();
	sf::Vector2f cameraSize = camera.getSize();
	sf::FloatRect cameraRect = sf::FloatRect(cameraCenter.x - cameraSize.x  * 0.5f, cameraCenter.y - cameraSize.y  * 0.5f, cameraSize.x, cameraSize.y);
	int healthBarWidth;
	int lostWidth;
	float newBarX;

	player1->GetMain()->getBattlePortrait()->setPosition(cameraRect.left + 1.f, cameraRect.top + 3.f);
	player1->GetSupport()->getSupportPortrait()->setPosition(cameraRect.left + 6.f, cameraRect.top + 36.f);

	// Player 1 Health Bars
	healthBarBackgroundSprite.setPosition(cameraRect.left + 30.f, cameraRect.top + 20.f);
	healthBarWidth = healthBarForeground->getSize().x * player1->GetMain()->GetPercentHealth();
	lostWidth = healthBarForeground->getSize().x * (1.f - player1->GetMain()->GetPercentHealth());
	healthBarForegroundSprite.setTextureRect(sf::IntRect(lostWidth, 0.f, healthBarWidth, healthBarForeground->getSize().y));
	healthBarForegroundSprite.setPosition(healthBarBackgroundSprite.getPosition().x + 2.f + (lostWidth * 0.35f), cameraRect.top + 18.f);

	healthBarWidth = healthBarForeground->getSize().x * player1->GetMain()->GetPercentRedHealth();
	lostWidth = healthBarForeground->getSize().x * (1.f - player1->GetMain()->GetPercentRedHealth());
	redBarForegroundSprite.setTextureRect(sf::IntRect(lostWidth, 0.f, healthBarWidth, redBarForeground->getSize().y));
	redBarForegroundSprite.setPosition(healthBarBackgroundSprite.getPosition().x + 2.f + (lostWidth * 0.35f), cameraRect.top + 18.f);

	// Player 1 Assist Health Bars
	if (player1->GetSupport()->isPlayable) {
		healthBarBackgroundSpriteP1Assist.setPosition(cameraRect.left + 36.f, cameraRect.top + 41.f);
		healthBarWidth = healthBarForeground->getSize().x * player1->GetSupport()->GetPercentHealth();
		lostWidth = healthBarForeground->getSize().x * (1.f - player1->GetSupport()->GetPercentHealth());
		healthBarForegroundSpriteP1Assist.setTextureRect(sf::IntRect(lostWidth, 0.f, healthBarWidth, healthBarForeground->getSize().y * 0.5f));
		healthBarForegroundSpriteP1Assist.setPosition(healthBarBackgroundSpriteP1Assist.getPosition().x + 1.f + (lostWidth * 0.35f), cameraRect.top + 40.f);

		healthBarWidth = healthBarForeground->getSize().x * player1->GetSupport()->GetPercentRedHealth();
		lostWidth = healthBarForeground->getSize().x * (1.f - player1->GetSupport()->GetPercentRedHealth());
		redBarForegroundSpriteP1Assist.setTextureRect(sf::IntRect(lostWidth, 0.f, healthBarWidth, redBarForeground->getSize().y * 0.5f));
		redBarForegroundSpriteP1Assist.setPosition(healthBarBackgroundSpriteP1Assist.getPosition().x + 1.f + (lostWidth * 0.35f), cameraRect.top + 40.f);
	}

	player2->GetMain()->getBattlePortrait()->setPosition(cameraRect.left + cameraRect.width - 1.f, cameraRect.top + 3.f);
	player2->GetMain()->getBattlePortrait()->setScale(-0.75f, 0.75f);
	player2->GetSupport()->getSupportPortrait()->setPosition(cameraRect.left + cameraRect.width - 6.f, cameraRect.top + 36.f);
	player2->GetSupport()->getSupportPortrait()->setScale(-0.75f, 0.75f);

	// Player 2 Health Bars
	healthBarBackgroundSpriteP2.setPosition(cameraRect.left + cameraRect.width - 30.f, cameraRect.top + 20.f);
	healthBarWidth = healthBarForeground->getSize().x * player2->GetMain()->GetPercentHealth();
	lostWidth = healthBarForeground->getSize().x * (1.f - player2->GetMain()->GetPercentHealth());
	healthBarForegroundSpriteP2.setTextureRect(sf::IntRect(lostWidth, 0.f, healthBarWidth, healthBarForeground->getSize().y));
	healthBarForegroundSpriteP2.setPosition(healthBarBackgroundSpriteP2.getPosition().x - 2.f - (lostWidth * 0.35f), cameraRect.top + 18.f);

	healthBarWidth = healthBarForeground->getSize().x * player2->GetMain()->GetPercentRedHealth();
	lostWidth = healthBarForeground->getSize().x * (1.f - player2->GetMain()->GetPercentRedHealth());
	redBarForegroundSpriteP2.setTextureRect(sf::IntRect(lostWidth, 0.f, healthBarWidth, redBarForeground->getSize().y));
	redBarForegroundSpriteP2.setPosition(healthBarBackgroundSpriteP2.getPosition().x - 2.f - (lostWidth * 0.35f), cameraRect.top + 18.f);

	// Player 2 Assist Health Bars
	if (player2->GetSupport()->isPlayable) {
		healthBarBackgroundSpriteP2Assist.setPosition(cameraRect.left + cameraRect.width - 36.f, cameraRect.top + 41.f);
		healthBarWidth = healthBarForeground->getSize().x * player2->GetSupport()->GetPercentHealth();
		lostWidth = healthBarForeground->getSize().x * (1.f - player2->GetSupport()->GetPercentHealth());
		healthBarForegroundSpriteP2Assist.setTextureRect(sf::IntRect(lostWidth, 0.f, healthBarWidth, healthBarForeground->getSize().y * 0.5f));
		healthBarForegroundSpriteP2Assist.setPosition(healthBarBackgroundSpriteP2Assist.getPosition().x - 1.f - (lostWidth * 0.35f), cameraRect.top + 40.f);

		healthBarWidth = healthBarForeground->getSize().x * player2->GetSupport()->GetPercentRedHealth();
		lostWidth = healthBarForeground->getSize().x * (1.f - player2->GetSupport()->GetPercentRedHealth());
		redBarForegroundSpriteP2Assist.setTextureRect(sf::IntRect(lostWidth, 0.f, healthBarWidth, redBarForeground->getSize().y * 0.5f));
		redBarForegroundSpriteP2Assist.setPosition(healthBarBackgroundSpriteP2Assist.getPosition().x - 1.f - (lostWidth * 0.35f), cameraRect.top + 40.f);
	}


	// Player 1 Special bar
	healthBarWidth = (int)(specialBarForeground->getSize().x * player1->GetMain()->GetPercentOneSpecialbar());
	specialBarForegroundSprite.setTextureRect(sf::IntRect(0.f, 0.f, (int)healthBarWidth, specialBarForeground->getSize().y));

	specialBarBackgroundSprite.setPosition(cameraRect.left + 15.f, cameraRect.top + cameraRect.height - 10.f - (specialBarBackground->getSize().y * specialBarBackgroundSprite.getScale().y));
	newBarX = (specialBarBackgroundSprite.getPosition().x + 28.f);
	specialBarForegroundSprite.setPosition(newBarX, specialBarBackgroundSprite.getPosition().y + 14.f);

	// Player 2 Special Bar
	healthBarWidth = (int)(specialBarForeground->getSize().x * player2->GetMain()->GetPercentOneSpecialbar());
	specialBarForegroundSpriteP2.setTextureRect(sf::IntRect(0.f, 0.f, (int)healthBarWidth, specialBarForeground->getSize().y));

	specialBarBackgroundSpriteP2.setPosition(cameraRect.left + cameraRect.width - 15.f, cameraRect.top + cameraRect.height - 10.f - (specialBarBackground->getSize().y * specialBarBackgroundSprite.getScale().y));
	specialBarForegroundSpriteP2.setPosition(specialBarBackgroundSpriteP2.getPosition().x - 28.f, specialBarBackgroundSpriteP2.getPosition().y + 14.f);

	readyTextSprite.setPosition(camera.getCenter());
	fightTextSprite.setPosition(camera.getCenter());
	KOTextSprite.setPosition(camera.getCenter());
}

Player* Fight::GetPlayer(int playerNumber) {
	switch (playerNumber) {
	case 1:
		return player1;
	case 2:
		return player2;
	default:
		printf("INVALID PLAYER NUMBER");
		return nullptr;
	}
}

Stage* Fight::GetStage() {
	return stage;
}

sf::View Fight::GetCamera() {
	return camera;
}

void Fight::ResetCombo(int playerExclude) {

	if (1 != playerExclude) player1->ResetCombo();
	if (2 != playerExclude) player2->ResetCombo();
}

void Fight::CreateHitSpark(sf::Vector2f position, int dLevel, int xScale) {
	if (0 == dLevel)
		return;

	Animation* newHitSpark = new Animation;
	switch (dLevel)
	{
	case -1:
		*newHitSpark = *hyperSpark;
		doingHyperSpark = true;
		camera.setCenter(position);
		hitSound.setBuffer(hyperSFX);
		hitSound.play();
		break;
	case 3:
		*newHitSpark = *heavySpark;
		hitSound.setBuffer(heavySFX);
		hitSound.play();
		break;
	case 2:
		*newHitSpark = *mediumSpark;
		hitSound.setBuffer(mediumSFX);
		hitSound.play();
		break;
	case 1:
		*newHitSpark = *lightSpark;
		hitSound.setBuffer(lightSFX);
		hitSound.play();
		break;
	case 4:
		*newHitSpark = *guardSpark;
		hitSound.setBuffer(guardSFX);
		hitSound.play();
		break;
	default:
		return;
	}
	newHitSpark->SetPosition(position);
	newHitSpark->SetXScale(xScale);

	allHitSparks.push_back(*newHitSpark);
}

void Fight::LoadHitSparks() {
	std::string filename = "Textures/Misc/HitSparks/";
	lightSpark = new Animation(filename, "Light", 6, false);
	lightSpark->SetFramesOfAnimation(12);
	mediumSpark = new Animation(filename, "Medium", 6, false);
	mediumSpark->SetFramesOfAnimation(12);
	heavySpark = new Animation(filename, "Heavy", 6, false);
	heavySpark->SetFramesOfAnimation(12);
	guardSpark = new Animation(filename, "Guard", 7, false);
	guardSpark->SetFramesOfAnimation(14);
	hyperSpark = new Animation(filename, "Hyper", 21, false);
	hyperSpark->SetFramesOfAnimation(42);
}

void Fight::FocusOnPlayer(int playerNo) {
	isFocusing = true;
	focusOnPlayer = playerNo;
}

void Fight::LoseFocus() {
	isFocusing = false;
	focusOnPlayer = -1;
}

void Fight::Pause(int playerNum, sf::Texture& commandListTexture) {
	isPaused = !isPaused;
	pauseMenu->SetPosition(camera);
	pauseMenu->SetPlayerNumber(playerNum, commandListTexture);
}

void Fight::StartEndCountdown() {
	endCountdown = 120;
}

void Fight::DrawGameTimer(sf::RenderWindow* window) {
	int gameTime = timeLimit / 60;

	timerDigit1.setTexture(numberTextures[gameTime / 10]);
	timerDigit1.setScale(0.35f, 0.35f);
	timerDigit1.setPosition(camera.getCenter().x - 17.f, camera.getCenter().y - 115.f);
	window->draw(timerDigit1);

	timerDigit2.setTexture(numberTextures[gameTime % 10]);
	timerDigit2.setScale(0.35f, 0.35f);
	timerDigit2.setPosition(camera.getCenter().x + 0.f, camera.getCenter().y - 115.f);
	window->draw(timerDigit2);
}

void Fight::ShowKOText() {
	announcerSound.setBuffer(koSFX);
	announcerSound.play();
	showKO = true;
}

void Fight::SetUpTrainingMatch() {
	disableWinCondition = true;
}

void Fight::SetUpLocalVersus() {
	disableWinCondition = false;
}

bool Fight::IsWinDisabled() {
	return disableWinCondition;
}

void Fight::StopAllNoise() {
	bgMusic.stop();
	announcerSound.stop();
	hitSound.stop();
}

void Fight::PlayerIntroDone(int playerNumber) {
	if (2 == playerNumber)
		p2IntroDone = true;
	else if (1 == playerNumber)
		p1IntroDone = true;

	allIntrosDone = (p1IntroDone && p2IntroDone);
	if (allIntrosDone) {
		announcerSound.setBuffer(readySFX);
		announcerSound.play();
	}
}