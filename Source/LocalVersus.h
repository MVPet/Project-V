#pragma once

#include "Scene.h"

class Fight;

class LocalVersus : public Scene
{
public:
	LocalVersus();
	~LocalVersus();


	void Start();
	void UpdateEvent(sf::Event event);
	void Update();
	void Draw(sf::RenderWindow * window);

private:
	Fight* fight;
};

const std::string LOCAL_VERSUS = "Local_Versus";