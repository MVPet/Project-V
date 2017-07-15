#pragma once

#include <SFML\Graphics.hpp>

class Scene
{
public:
	virtual void Start() =0;
	virtual void UpdateEvent(sf::Event event) =0;
	virtual void Update() = 0;
	virtual void Draw(sf::RenderWindow* window) = 0;

protected:
	bool sceneDone = false;
};