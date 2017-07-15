#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Stage
{
public:

	void Update(sf::View camera);
	virtual void Load(std::string stageName);
	void DrawBackground(sf::RenderWindow* window);
	void DrawForeground(sf::RenderWindow* window);

	sf::Vector2f GetCenter();
	sf::Vector2f GetPlayer1Spawn();
	sf::Vector2f GetPlayer2Spawn();

	float GetLeftBound();
	float GetRightBound();
	float GetBottomBound();
	float GetStageBottom();

private:

	void DrawBounds(sf::RenderWindow* window);

	//sf::Texture* backgroundLayersTextures;
	//sf::Texture* backgroundSpriteTextures;

	//sf::Texture* foregroundLayersTextures;
	//sf::Texture* foregroundSpriteTextures;

	std::vector<sf::Texture> backgroundLayersTextures;
	//std::vector<sf::Texture> backgroundLayersSprites;
	sf::Sprite* backgroundLayersSprites;

	//std::vector<sf::Texture> foregroundLayersTextures;
	//std::vector<sf::Texture> foregroundLayersSprites;
	//sf::Sprite* foregroundLayersSprites;


	//sf::Texture backgroundTexture;
	//sf::Sprite backgroundSprite;

	sf::Texture foregroundTexture;
	sf::Sprite foregroundSprite;

	//sf::FloatRect leftBoundary;
	//sf::FloatRect rightBoundary;
	//sf::FloatRect floorBoundary;

	sf::Vector2f player1Spawn;
	sf::Vector2f player2Spawn;

	float leftBound;
	float rightBound;
	float bottomBound;
	float stageBottom;

	int numberOfBackgroundLayers = 0;
};