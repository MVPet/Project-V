#pragma once

#include <SFML/Graphics.hpp>

class SceneManager;

class GameManager
{
public:
	GameManager();
	~GameManager();

	void run();

	static const float TIME_PER_FRAME;

	int slowdownTimer = 0;
	float gameSpeed = 1.f;

private:

	sf::RenderWindow* window;
	SceneManager* sceneManager;
	float updateTimer;
	float drawSlowdownTimer;
	bool inFocus = true;

	sf::Shader testShader;
	sf::Texture testTexture;
	sf::Sprite testSprite;
	sf::Texture testTexture2;
	sf::Sprite testSprite2;
};