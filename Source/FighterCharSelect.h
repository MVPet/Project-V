#pragma once

#include <string>
#include "Animation.h"

class FighterCharSelect {
public:
	FighterCharSelect();
	~FighterCharSelect();

	void Load(std::string name, float newOffset = 0);
	void Update();
	void DrawPortrait(sf::RenderWindow* window);
	void DrawCurrentAnimation(sf::RenderWindow* window);
	void Unselected();
	void Selected();
	void UseAltColor();
	int GetAltColorUsage();

	void SetPortraitPosition(sf::Vector2f newPosition, float positionOffset, int side);
	sf::Vector2f GetPortraitPosition();
	void SetAnimationPosition(sf::Vector2f newPosition);
	void SetXScale(int newXScale);
	std::string GetName();

	void operator=(const FighterCharSelect& copy) {
		charName = copy.charName;
		idleAnim = new Animation();
		*idleAnim = *copy.idleAnim;
		selectedAnim = new Animation();
		*selectedAnim = *copy.selectedAnim;
		currentAnimation = copy.currentAnimation;
		portraitTexture = copy.portraitTexture;
		portraitSprite = copy.portraitSprite;
		nameTexture = copy.nameTexture;
		nameSprite = copy.nameSprite;
		yOffset = copy.yOffset;
		colorUse = copy.colorUse;
	}

private:
	std::string charName;
	Animation* idleAnim;
	Animation* selectedAnim;
	Animation currentAnimation;

	sf::Texture portraitTexture;
	sf::Sprite portraitSprite;

	sf::Texture nameTexture;
	sf::Sprite nameSprite;

	sf::Vector2f animationPosition;
	sf::Vector2f portraitPosition;

	float yOffset;

	int xScale = 1;

	sf::Shader colorShader;
	int colorUse = 1;

	const std::string IDLE = "Idle";
	const std::string SUPPORT_END = "Support_End";
};