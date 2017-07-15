#pragma once

#include "Scene.h"

class Fight;

class Training : public Scene
{
public:
	Training();
	~Training();

	void Start();
	void UpdateEvent(sf::Event event);
	void Update();
	void Draw(sf::RenderWindow * window);

private:
	Fight* fight;
};

const std::string TRAINING = "Training";