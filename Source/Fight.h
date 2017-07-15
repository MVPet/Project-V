#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Stage.h"
#include "Player.h"
#include "Animation.h"
#include "PauseMenu.h"
#include "PostGameMenu.h"

class Fight
{
public:
	Fight();
	~Fight();

	void UpdateEvent(sf::Event event);
	void Update();
	void Draw(sf::RenderWindow* window);

	static Player* GetPlayer(int playerNumber);
	static Stage* GetStage();
	static sf::View GetCamera();
	static void ResetCombo(int playerExclude);
	static void FocusOnPlayer(int playerNo);
	static void LoseFocus();
	static void Pause(int playerNum, sf::Texture& commandListTexture);
	static void StopAllNoise();
	void CheckForVictory();
	static void StartEndCountdown();
	static bool IsWinDisabled();
	static void PlayerIntroDone(int playerNumber);

	// NOT REALLY SURE WHY THESE ARE HERE, EH I'LL TAKE CARE OF IT LATER
	static void LoadHitSparks();
	void UpdateHitSparks();
	static void CreateHitSpark(sf::Vector2f position, int dLevel, int xScale);
	void DrawHitSparks(sf::RenderWindow* window);
	void DrawCombo(sf::RenderWindow* window);
	void DrawSpecialBarNumbers(sf::RenderWindow* window);
	void DrawGameTimer(sf::RenderWindow* window);

	void SetUpTrainingMatch();
	void SetUpLocalVersus();
	void RestoreDefaults();
	//void ShowAttackData();

	static void ShowKOText();

	static bool p1HyperSwap;
	static bool p2HyperSwap;
	static bool cameraLock;

private:
	void UpdateCamera();
	void UpdateHUD();

	static Player* player1;
	static Player* player2;
	static Stage* stage;

	static sf::View camera;
	static float cameraJumpBound;
	static float cameraBaseY;
	static bool isFocusing;
	static int focusOnPlayer;
	static bool doingHyperSpark;


	static std::vector<Animation> allHitSparks;
	static Animation* lightSpark;
	static Animation* mediumSpark;
	static Animation* heavySpark;
	static Animation* guardSpark;
	static Animation* hyperSpark;

	sf::Texture numberTextures[10];
	sf::Sprite comboDigit1P1;
	sf::Sprite comboDigit1P2;
	sf::Sprite comboDigit2P1;
	sf::Sprite comboDigit2P2;
	sf::Sprite comboDigit3P1;
	sf::Sprite comboDigit3P2;
	sf::Texture hitsTexture;
	sf::Sprite hitsSpriteP1;
	sf::Sprite hitsSpriteP2;

	sf::Sprite timerDigit1;
	sf::Sprite timerDigit2;

	sf::Texture* hyperTexture;

	sf::Texture* healthBarBackground;
	sf::Sprite healthBarBackgroundSprite;
	sf::Sprite healthBarBackgroundSpriteP1Assist;
	sf::Sprite healthBarBackgroundSpriteP2;
	sf::Sprite healthBarBackgroundSpriteP2Assist;
	sf::Texture* healthBarForeground;
	sf::Sprite healthBarForegroundSprite;
	sf::Sprite healthBarForegroundSpriteP1Assist;
	sf::Sprite healthBarForegroundSpriteP2;
	sf::Sprite healthBarForegroundSpriteP2Assist;
	sf::Texture* redBarForeground;
	sf::Sprite redBarForegroundSprite;
	sf::Sprite redBarForegroundSpriteP1Assist;
	sf::Sprite redBarForegroundSpriteP2;
	sf::Sprite redBarForegroundSpriteP2Assist;
	sf::Texture* specialBarBackground;
	sf::Sprite specialBarBackgroundSprite;
	sf::Sprite specialBarBackgroundSpriteP1Assist;
	sf::Sprite specialBarBackgroundSpriteP2;
	sf::Sprite specialBarBackgroundSpriteP2Assist;
	sf::Texture* specialBarForeground;
	sf::Sprite specialBarForegroundSprite;
	sf::Sprite specialBarForegroundSpriteP1Assist;
	sf::Sprite specialBarForegroundSpriteP2;
	sf::Sprite specialBarForegroundSpriteP2Assist;
	sf::Sprite specialValueP1Sprite;
	sf::Sprite specialValueP2Sprite;

	sf::Texture readyTextTexture;
	sf::Sprite readyTextSprite;

	sf::Texture fightTextTexture;
	sf::Sprite fightTextSprite;

	sf::Texture p1WinTexture;
	sf::Texture p2WinTexture;
	sf::Texture tieTesture;
	sf::Sprite winnerSprite;

	static bool showKO;
	sf::Texture KOTextTexure;
	sf::Sprite KOTextSprite;

	sf::Font font;
	sf::Texture blackBackground;

	static bool isPaused;
	static PauseMenu* pauseMenu;

	bool showPostGameMenu = false;
	PostGameMenu postGameMenu;

	const int FRAMES_TO_READY = 120;
	bool readyIntro = true;
	int readyIntroTimer = FRAMES_TO_READY;

	bool fightIsOver = false;

	int timeLimit = 5940;

	static int endCountdown;
	int fightTextTimer = 45;

	static bool disableWinCondition;
	bool disableGameTime = false;

	static sf::SoundBuffer readySFX;
	static sf::SoundBuffer fightSFX;
	static sf::SoundBuffer lightSFX;
	static sf::SoundBuffer mediumSFX;
	static sf::SoundBuffer heavySFX;
	static sf::SoundBuffer guardSFX;
	static sf::SoundBuffer hyperSFX;
	static sf::SoundBuffer koSFX;

	static sf::Sound announcerSound;
	static sf::Sound hitSound;

	static sf::Music bgMusic;

	static bool p1IntroDone;
	static bool p2IntroDone;
	static bool allIntrosDone;
};