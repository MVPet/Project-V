#pragma once

#include <SFML/Graphics.hpp>

static const sf::Vector2f GetTextureCenter(sf::Texture* texture) {
	return sf::Vector2f(texture->getSize().x * 0.5f, texture->getSize().y * 0.5f);
}