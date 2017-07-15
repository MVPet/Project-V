#include "AnimationManager.h"
#include "ApplicationData.h"
#include "Fighter.h"

#include<iostream>

AnimationManager::AnimationManager()
{}

AnimationManager::~AnimationManager()
{}

// CONSIDER DOING A TEMPLATE FOR THIS
void AnimationManager::Update(sf::Vector2f position, int xScale, Fighter* animOwner)
{
	if (!stopped)
	{
		if (0 >= pauseTime) {
			currentAnimation.Update(position, xScale, animOwner);

			if (IsCurrentAnimationDone() && "" != currentAnimation.GetAnimToPlayWhenDone())
				PlayAnimChain(currentAnimation.GetAnimToPlayWhenDone(), position, xScale);
		}
		else
			pauseTime -= ApplicationData::deltaTime;
	}
}

// CONSIDER DOING A TEMPLATE FOR THIS
void AnimationManager::Update(sf::Vector2f position, int xScale, Projectile* animOwner)
{
	if (!stopped)
	{
		if (0 >= pauseTime) {
			currentAnimation.Update(position, xScale, animOwner);

			if (IsCurrentAnimationDone() && "" != currentAnimation.GetAnimToPlayWhenDone())
				PlayAnimChain(currentAnimation.GetAnimToPlayWhenDone(), position, xScale);
				//Play(currentAnimation.GetAnimToPlayWhenDone());
		}
		else
			pauseTime -= ApplicationData::deltaTime;
	}
}

void AnimationManager::Draw(sf::RenderWindow* window, sf::Color hue)
{
	currentAnimation.Draw(window, hue);
}

void AnimationManager::Draw(sf::RenderWindow* window, sf::Shader& shader) {
	currentAnimation.Draw(window, shader);
}

void AnimationManager::AddAnimation(std::string animName, std::string animFilePath, int numOfFrames, bool loop, std::string nextAnim)
{
	Animation* animation = new Animation(animFilePath, animName, numOfFrames, loop, nextAnim);
	animationList.insert(std::make_pair(animName, animation));
}

void AnimationManager::AddAnimation(std::string animName, Animation* animation)
{
	animationList.insert(std::make_pair(animName, animation));
}

void AnimationManager::Play(std::string animName, sf::Vector2f position, int xScale)
{
	if (nameOfCurrentAnim != animName && "" != animName)
	{
		Animation tempAnim = *(animationList.find(animName)->second);
		tempAnim.SetPosition(position);
		tempAnim.SetXScale(xScale);
		tempAnim.ReUpdateBoxes(position, xScale);
		currentAnimation = tempAnim;
		nameOfCurrentAnim = animName;
	}
}

void AnimationManager::PlayAnimChain(std::string animName, sf::Vector2f position, int xScale)
{
	if (nameOfCurrentAnim != animName)
	{
		Animation tempAnim = *(animationList.find(animName)->second);
		tempAnim.SetPosition(position);
		tempAnim.SetXScale(xScale);
		tempAnim.ReUpdateBoxes(position, xScale);
		currentAnimation = tempAnim;
		nameOfCurrentAnim = animName;
	}
}

void AnimationManager::Pause(float pauseLength)
{
	pauseTime = pauseLength;
}

void AnimationManager::Stop()
{
	stopped = true;
}

void AnimationManager::Resume()
{
	stopped = false;
}

void AnimationManager::Restart()
{
	currentAnimation.Restart();
}

bool AnimationManager::IsCurrentAnimationDone() {
	return currentAnimation.IsDone();
}

Animation* AnimationManager::GetCurrentAnimation() {
	return &currentAnimation;
}

std::string AnimationManager::GetCurrentAnimationName() {
	return nameOfCurrentAnim;
}

Animation* AnimationManager::GetAnimation(std::string animName) {
	return animationList.find(animName)->second;
}

void AnimationManager::ReUpdateAnimationBoxes(sf::Vector2f position, int xScale) {
	currentAnimation.ReUpdateBoxes(position, xScale);
}