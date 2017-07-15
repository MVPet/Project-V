#include "FighterCharSelect.h"
#include "Utilities.h"
#include "FighterStrings.h"
#include <iostream>

FighterCharSelect::FighterCharSelect() {
}

FighterCharSelect::~FighterCharSelect() {
	delete idleAnim;
	delete selectedAnim;
}

void FighterCharSelect::Load(std::string name, float newOffset) {
	charName = name;

	std::string filename = "Textures/Chars/" + name + "/";

	if (!portraitTexture.loadFromFile(filename + "Portraits/CharSelect.png"))
		std::cout << "CANNOT LOAD " << name << "CHAR SELECT PORTRAIT" << std::endl;
	portraitSprite.setTexture(portraitTexture);
	portraitSprite.setOrigin(GetTextureCenter(&portraitTexture));

	if (!nameTexture.loadFromFile(filename + "Portraits/Name.png"))
		std::cout << "CANNOT LOAD " << name << "CHAR SELECT PORTRAIT" << std::endl;
	nameSprite.setTexture(nameTexture);
	nameSprite.setOrigin(sf::Vector2f(GetTextureCenter(&nameTexture).x, GetTextureCenter(&nameTexture).y * 2.f)); // Make Origin on text the bottom (allows for multi line names)
	nameSprite.setScale(0.35f, 0.35f);

	idleAnim = new Animation(filename, IDLE, -1, true);

	selectedAnim = new Animation(filename, SUPPORT_END, -1, false);

	yOffset = newOffset;

	Unselected();
}

void FighterCharSelect::Update() {
	currentAnimation.Update();
}

void FighterCharSelect::Unselected() {
	Animation tempAnim = *idleAnim;
	tempAnim.SetPosition(animationPosition);
	tempAnim.SetXScale(xScale);
	currentAnimation = tempAnim;
}

void FighterCharSelect::Selected() {
	Animation tempAnim = *selectedAnim;
	tempAnim.SetPosition(animationPosition);
	tempAnim.SetXScale(xScale);
	currentAnimation = tempAnim;
}

void FighterCharSelect::DrawPortrait(sf::RenderWindow* window) {
	window->draw(portraitSprite);
}

void FighterCharSelect::DrawCurrentAnimation(sf::RenderWindow* window) {
	currentAnimation.SetPosition(sf::Vector2f(animationPosition.x, animationPosition.y +yOffset));
	currentAnimation.SetXScale(xScale);
	//currentAnimation.Draw(window, sf::Color::White);
	currentAnimation.Draw(window, colorShader);

	nameSprite.setPosition(animationPosition.x, 515.f);
	window->draw(nameSprite);
}

void FighterCharSelect::SetPortraitPosition(sf::Vector2f newPosition, float positionOffset, int side) {
	portraitPosition = newPosition;
	//portraitPosition.x += portraitTexture.getSize().x * 0.5f * (positionOffset * 2 + (1 * side));
	portraitPosition.x += (portraitTexture.getSize().x + 2) * (positionOffset * side);
	portraitSprite.setScale((float)-side, 1.f);
	portraitSprite.setPosition(portraitPosition);
}

sf::Vector2f FighterCharSelect::GetPortraitPosition() {
	return portraitPosition;
}

void FighterCharSelect::SetAnimationPosition(sf::Vector2f newPosition) {
	animationPosition = newPosition;
}

void FighterCharSelect::SetXScale(int newXScale) {
	xScale = newXScale;
}

std::string FighterCharSelect::GetName() {
	return charName;
}

void FighterCharSelect::UseAltColor() {
	if (!colorShader.loadFromFile("Shaders/ColorTest.frag", sf::Shader::Fragment))
		std::cout << "CANNOT LOAD COLOR SHADER" << std::endl;

	colorUse = 2;
	colorShader.setParameter("texture", sf::Shader::CurrentTexture);

	if (RYU == charName) {
		colorShader.setParameter("color1", 1.f, 1.f, 0.937f);
		colorShader.setParameter("replace1", 0.235f, 0.235f, 0.219f);
		colorShader.setParameter("color2", 0.807f, 0.741f, 0.580f);
		colorShader.setParameter("replace2", 0.188f, 0.172f, 0.137f);
		colorShader.setParameter("color3", 0.678f, 0.647f, 0.517f);
		colorShader.setParameter("replace3", 0.167f, 0.152f, 0.121f);
		colorShader.setParameter("color4", 0.517f, 0.517f, 0.419f);
		colorShader.setParameter("replace4", 0.121f, 0.121f, 0.098f);
		colorShader.setParameter("color5", 0.905f, 0.905f, 0.776f);
		colorShader.setParameter("replace5", 0.211f, 0.211f, 0.184f);
		colorShader.setParameter("color6", 0.968f, 0.f, 0.f);
		colorShader.setParameter("replace6", 0.f, 0.494f, 0.847f);
		colorShader.setParameter("color7", 0.709f, 0.f, 0.f);
		colorShader.setParameter("replace7", 0.f, 0.290f, 0.498f);
	}
	else if (KYOSUKE == charName) {
		colorShader.setParameter("color1", 1.f, 1.f, 1.f);
		colorShader.setParameter("replace1", 0.322f, 0.322f, 0.969f);
		colorShader.setParameter("color2", 0.808f, 0.839f, 0.968f);
		colorShader.setParameter("replace2", 0.259f, 0.192f, 0.870f);
		colorShader.setParameter("color3", 0.580f, 0.611f, 0.776f);
		colorShader.setParameter("replace3", 0.224f, 0.129f, 0.678f);
		colorShader.setParameter("color4", 0.451f, 0.482f, 0.678f);
		colorShader.setParameter("replace4", 0.129f, 0.031f, 0.451f);
		colorShader.setParameter("color5", 0.647f, 0.f, 0.f);
		colorShader.setParameter("replace5", 0.549f, 0.678f, 0.549f);
		colorShader.setParameter("color6", 0.451f, 0.f, 0.f);
		colorShader.setParameter("replace6", 0.388f, 0.482f, 0.388f);
		colorShader.setParameter("color7", 0.223f, 0.223f, 0.321f);
		colorShader.setParameter("replace7", 0.580f, 0.192f, 0.450f);
	}
	else if (SAKI == charName) {
		colorShader.setParameter("color1", 0.941f, 0.f, 0.f);
		colorShader.setParameter("replace1", 0.752f, 0.878f, 0.941f);
		colorShader.setParameter("color2", 0.690f, 0.f, 0.f);
		colorShader.setParameter("replace2", 0.501f, 0.564f, 0.815f);
		colorShader.setParameter("color3", 0.439f, 0.f, 0.f);
		colorShader.setParameter("replace3", 0.250f, 0.313f, 0.501f);
		colorShader.setParameter("color4", 0.376f, 0.439f, 0.501f);
		colorShader.setParameter("replace4", 0.501f, 0.439f, 0.439f);
		colorShader.setParameter("color5", 0.752f, 0.752f, 0.815f);
		colorShader.setParameter("replace5", 0.815f, 0.752f, 0.752f);
		colorShader.setParameter("color6", 0.250f, 0.250f, 0.313f);
		colorShader.setParameter("replace6", 0.313f, 0.250f, 0.250f);
	}
	else if (TON_POOH == charName) {
		colorShader.setParameter("color1", 0.690f, 0.690f, 0.690f);
		colorShader.setParameter("replace1", 0.188f, 0.188f, 0.188f);
		colorShader.setParameter("color2", 0.564f, 0.564f, 0.564f);
		colorShader.setParameter("replace2", 0.125f, 0.125f, 0.125f);
		colorShader.setParameter("color3", 0.313f, 0.313f, 0.313f);
		colorShader.setParameter("replace3", 0.f, 0.f, 0.f);
		colorShader.setParameter("color4", 0.878f, 0.878f, 0.878f);
		colorShader.setParameter("replace4", 0.313f, 0.313f, 0.313f);
		colorShader.setParameter("color5", 0.752f, 0.752f, 0.752f);
		colorShader.setParameter("replace5", 0.250f, 0.250f, 0.250f);
		colorShader.setParameter("color6", 0.941f, 0.941f, 0.941f);
		colorShader.setParameter("replace6", 0.627f, 0.627f, 0.627f);
		colorShader.setParameter("color7", 0.439f, 0.439f, 0.439f);
		colorShader.setParameter("replace7", 0.062f, 0.062f, 0.062f);
	}
}

int FighterCharSelect::GetAltColorUsage() {
	return colorUse;
}