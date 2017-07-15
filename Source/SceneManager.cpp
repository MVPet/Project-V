#include <stdio.h>

#include <SFML\Graphics.hpp>

#include "SceneManager.h"
#include "SceneInitializer.h"
#include <iostream>

SceneManager::SceneManager()
{
	currentScene = nullptr;

	if (!loadingTexture.loadFromFile("Textures/Scenes/Loading.png"))
		std::cout << "CANNOT LOAD LOADING" << std::endl;
	loadingSprite.setTexture(loadingTexture);
}

SceneManager::~SceneManager()
{
	delete currentScene;
}

void SceneManager::SetCurrentScene(std::string sceneName)
{
	nextScene = sceneName;
	sceneFinished = true;
	/*
	Scene* newScene = InitializeScene(sceneName);

	if (nullptr != newScene)
	{
		delete currentScene;

		currentScene = newScene;

		currentScene->Start();
	}
	*/
}

void SceneManager::UpdateEvent(sf::Event event)
{
	if (nullptr != currentScene)
		currentScene->UpdateEvent(event);
}

void SceneManager::Update()
{
	if (sceneFinished) {
		Scene* newScene = InitializeScene(nextScene);

		if (nullptr != newScene)
		{
			delete currentScene;

			currentScene = newScene;

			currentScene->Start();
		}
		sceneFinished = false;
		return;
	}

	if (nullptr != currentScene)
		currentScene->Update();
}

void SceneManager::Draw(sf::RenderWindow* window)
{
	if (sceneFinished) {
		//window->setView(window->getDefaultView());
		sf::View temp;
		temp.setSize(sf::Vector2f(1280, 720));
		temp.setCenter(sf::Vector2f(640, 360));
		window->setView(temp);

		window->draw(loadingSprite);
		return;
	}

	if (nullptr != currentScene)
		currentScene->Draw(window);
}