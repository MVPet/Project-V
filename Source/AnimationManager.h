#pragma once

#include <SFML\Graphics.hpp>
#include <unordered_map>
#include <string>

#include "Animation.h"

class Fighter;
class Projectile;

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();

	// CONSIDER DOING A TEMPLATE FOR THIS
	virtual void Update(sf::Vector2f position, int xScale, Fighter* animOwner);
	virtual void Update(sf::Vector2f position, int xScale, Projectile* animOwner);
	void ReUpdateAnimationBoxes(sf::Vector2f position, int xScale);

	void Draw(sf::RenderWindow* window, sf::Shader& shader);
	void Draw(sf::RenderWindow* window, sf::Color hue);

	void AddAnimation(std::string animName, std::string animFilePath, int numOfFrames, bool loop, std::string nextAnim = "Idle");
	void AddAnimation(std::string animName, Animation*);

	void Play(std::string animName, sf::Vector2f position, int xScale);
	void PlayAnimChain(std::string animName, sf::Vector2f position, int xScale);
	void Pause(float pauseTime);
	void Stop();
	void Resume();
	void Restart();

	bool IsCurrentAnimationDone();
	Animation* GetCurrentAnimation();
	std::string GetCurrentAnimationName();
	Animation* GetAnimation(std::string animName);

private:
	std::string nameOfCurrentAnim;
	bool stopped = false;
	float pauseTime = 0;

	Animation currentAnimation;
	std::unordered_map<std::string, Animation*> animationList;
};