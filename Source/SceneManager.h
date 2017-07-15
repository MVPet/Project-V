#pragma once

#include "Scene.h"
#include "SceneInitializer.h"
#include <SFML\Graphics.hpp>

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void SetCurrentScene(std::string sceneName);
	void UpdateEvent(sf::Event event);
	void Update();
	void Draw(sf::RenderWindow* window);

private:
	Scene* currentScene;
	std::string nextScene = "";
	bool sceneFinished = false;

	sf::Texture loadingTexture;
	sf::Sprite loadingSprite;
};