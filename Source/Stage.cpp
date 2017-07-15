#include "Stage.h"
#include "GameManager.h"
#include "Fight.h"
#include <string>
#include <iostream>

void Stage::Update(sf::View camera)
{
	float cameraXCenter = Fight::GetCamera().getCenter().x;
	float newX = 0;
	float centerDiff = cameraXCenter - GetCenter().x;
	float numOfSegments = 1.f / (numberOfBackgroundLayers - 1.f);
	for (int i = numberOfBackgroundLayers - 1; i >= 1; i--) {
		newX = GetCenter().x + (centerDiff * (numOfSegments * ((float)i * 0.5f)));
		backgroundLayersSprites[i].setPosition(newX, backgroundLayersSprites[i].getPosition().y);
	}

	foregroundSprite.setPosition(backgroundLayersSprites[0].getPosition().x, foregroundSprite.getPosition().y);
}

void Stage::Load(std::string stageName)
{
	std::string bLayerPath = "Textures/Stages/" + stageName + "/BLayer";
	std::string filename = "";
	for (int i = 0;; i++) {
		filename = bLayerPath + std::to_string(numberOfBackgroundLayers++) + ".png";
		sf::Texture* newTexture = new sf::Texture();
		if (!newTexture->loadFromFile(filename)) {
			std::cout << "CANNOT LOAD BACKGROUND TEXTURE: " << i << std::endl;
			numberOfBackgroundLayers--;
			break;
		}
		//newTexture->setSmooth(true);////////////////////////////////////////////////////////////
		backgroundLayersTextures.push_back(*newTexture);
	}

	// SETUP THE SPRITES WITH THE TEXTURES
	backgroundLayersSprites = new sf::Sprite[numberOfBackgroundLayers];

	backgroundLayersSprites[0].setTexture(backgroundLayersTextures[0]);

	// SET THE ORIGIN TO THE CENTER
	for (int i = 1; i < numberOfBackgroundLayers; i++) {
		backgroundLayersSprites[i].setTexture(backgroundLayersTextures[i]);
		backgroundLayersSprites[i].setOrigin(backgroundLayersTextures[i].getSize().x * 0.5f, 0);
	}

	backgroundLayersSprites[numberOfBackgroundLayers - 1].setPosition(backgroundLayersSprites[numberOfBackgroundLayers - 1].getPosition().x, ((int)backgroundLayersTextures[0].getSize().y - (int)backgroundLayersTextures[numberOfBackgroundLayers - 1].getSize().y));

	
	filename = "Textures/Stages/" + stageName + "/FLayer0.png";
	if (!foregroundTexture.loadFromFile(filename))
	{
		printf("CANNOT LOAD FOREGROUND TEXTURE\n");
	}

	//foregroundTexture.setSmooth(true);////////////////////////////////////////////////////////////

	foregroundSprite.setTexture(foregroundTexture);
	foregroundSprite.setPosition(foregroundSprite.getPosition().x, ((int)backgroundLayersTextures[0].getSize().y - (int)foregroundTexture.getSize().y));

	leftBound = 0.f;
	rightBound = backgroundLayersTextures[0].getSize().x;
	bottomBound = backgroundLayersTextures[0].getSize().y * 0.85f;

	player1Spawn.y = bottomBound;
	player1Spawn.x = GetCenter().x - 50.f;

	player2Spawn.y = bottomBound;
	player2Spawn.x = GetCenter().x + 50.f;

	stageBottom = backgroundLayersTextures[0].getSize().y;
}

void Stage::DrawBounds(sf::RenderWindow* window)
{
}

void Stage::DrawBackground(sf::RenderWindow* window)
{
	window->draw(backgroundLayersSprites[numberOfBackgroundLayers - 1]);
	for (int i = numberOfBackgroundLayers - 1; i >= 0; i--) {
		window->draw(backgroundLayersSprites[i]);
	}

	DrawBounds(window);
}

void Stage::DrawForeground(sf::RenderWindow* window) {
	window->draw(foregroundSprite);
}

sf::Vector2f Stage::GetCenter()
{
	//sf::Vector2u textureSize = foregroundTexture.getSize();
	sf::Vector2u textureSize = backgroundLayersTextures[0].getSize();
	return sf::Vector2f(textureSize.x * 0.5f, textureSize.y * 0.5f);
}

sf::Vector2f Stage::GetPlayer1Spawn()
{
	return player1Spawn;
}

sf::Vector2f Stage::GetPlayer2Spawn()
{
	return player2Spawn;
}

float Stage::GetLeftBound()
{
	//return foregroundSprite.getPosition().x;
	return backgroundLayersSprites[0].getPosition().x;
}

float Stage::GetRightBound()
{
	//return foregroundSprite.getPosition().x + foregroundTexture.getSize().x;
	return backgroundLayersSprites[0].getPosition().x + backgroundLayersTextures[0].getSize().x;
}

float Stage::GetBottomBound()
{
	return bottomBound;
}

float Stage::GetStageBottom() {
	return stageBottom;
}