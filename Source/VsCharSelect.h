#pragma once


#include <SFML\Audio.hpp>
#include "Scene.h"
#include "Controls.h"
#include "FighterCharSelect.h"

class VsCharSelect : public Scene {
public:
	VsCharSelect();
	~VsCharSelect();

	void Start();
	void UpdateEvent(sf::Event event);
	void Update();
	void Draw(sf::RenderWindow * window);

private:

	bool CheckP1CharInputs();
	bool CheckP2CharInputs();
	bool CheckP1StageInputs();
	bool CheckP2StageInputs();
	void OnToTheFight();
	int GetRandomPlayable(int playerNo);
	int GetRandomSupport(int playerNo);

	void UpdateP1UI();
	void UpdateP2UI();

	int currentStageOption = 0;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Texture charTitleTexture;
	sf::Sprite charTitleSprite;
	sf::Texture stageTitleTexture;
	sf::Sprite stageTitleSprite;

	sf::Texture* stageSampleTextures;
	sf::Sprite	currentStageOptionSprite;
	sf::Texture arrowTexture;
	sf::Sprite leftArrowSprite;
	sf::Sprite rightArrowSprite;

	sf::View camera;
	FighterCharSelect* playableFighters;
	FighterCharSelect* supportFighters;

	FighterCharSelect p1Main;
	FighterCharSelect p1Support;

	FighterCharSelect p2Main;
	FighterCharSelect p2Support;

	Controls* p1Controls;
	int lastP1Vert = 0;
	int lastP1Horiz = 0;
	bool p1ConfirmHeld = true;
	bool p1CancelHeld = true;
	sf::Texture p1CursorTexture;
	sf::Texture p1Rand1CursorTexture;
	sf::Texture p1Rand2CursorTexture;
	sf::Sprite p1CursorSprite;
	sf::Sprite p1Rand1CursorSprite;
	sf::Sprite p1Rand2CursorSprite;
	const sf::Vector2f p1Position;
	sf::Vector2i p1CursorPosition = sf::Vector2i(1,0);
	bool p1MainSelected = false;
	bool p1SupportSelected = false;

	Controls* p2Controls;
	int lastP2Vert = 0;
	int lastP2Horiz = 0;
	bool p2ConfirmHeld = true;
	bool p2CancelHeld = true;
	sf::Texture p2CursorTexture;
	sf::Texture p2Rand1CursorTexture;
	sf::Texture p2Rand2CursorTexture;
	sf::Sprite p2CursorSprite;
	sf::Sprite p2Rand1CursorSprite;
	sf::Sprite p2Rand2CursorSprite;
	const sf::Vector2f p2Position;
	sf::Vector2i p2CursorPosition = sf::Vector2i(1, 0);
	bool p2MainSelected = false;
	bool p2SupportSelected = false;

	sf::Texture assistTextTexture;
	sf::Sprite assistTextSprite;

	//sf::SoundBuffer charSelectSFX;
	//sf::Sound		charSelectSound;
	sf::Music		charSelectMusic;

	sf::SoundBuffer cursorMoveSFX;
	sf::SoundBuffer cursorSelectSFX;
	sf::SoundBuffer cursorBackSFX;
	sf::Sound p1Sound;
	sf::Sound p2Sound;
};

const std::string VS_CHAR_SELECT = "Vs_Char_Select";