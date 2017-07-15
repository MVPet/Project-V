#include "Animation.h"
#include "Fighter.h"

#include "Utilities.h"

#include <iostream>
#include <stdio.h>
using namespace std;
typedef Animation::Origin Origin;


Animation::Animation() { // Blank constructor for empty animation
}

Animation::Animation(std::string filePath, std::string name, int totalFrames, bool loop, std::string nextAnimToPlay, int numberOfLoops)
	: numOfSprites(totalFrames)
	, looping(loop)
	, animName(name)
	, animToPlayWhenDone(nextAnimToPlay)
	, numOfLoops(numberOfLoops)
{
	if (-1 == totalFrames)
		LoadDynamic(filePath);
	else
		Load(filePath);
}

Animation::~Animation() {
}

void Animation::Load(std::string filePath) {
	int frameCount = 0;
	std::string filename = "";

	// SETUP THE TEXTURES
	//textureList = new sf::Texture[numOfSprites]; // Might need to initialize them all to nullptr first
	textureList.resize(numOfSprites);

	filePath += animName + "/";
	for (int i = 0; i < numOfSprites; i++) {
		filename = filePath + std::to_string(frameCount++) + ".png";
		if (!textureList[i].loadFromFile(filename))
			std::cout << "SKIPPING FRAME " << i << std::endl;
	}

	// SETUP THE SPRITES WITH THE TEXTURES
	spriteList = new sf::Sprite[numOfSprites]; // Might need to initialize them all to nullptr first

	// SET THE ORIGIN TO THE CENTER
	for (int i = 0; i < numOfSprites; i++) {
		spriteList[i].setTexture(textureList[i]);
		spriteList[i].setOrigin(textureList[i].getSize().x * 0.5f, textureList[i].getSize().y * 0.5f); // Set the Origin to the Center of the Texture, all frames should have the same size sprite
	}

	currentSprite = spriteList[0];


	framesPerSprite = new int[numOfSprites];

	//////////////////// SETUP HOW MANY FRAMES EACH SPRITE IS OUT FOR
	// WILL EVENTUALLY USE JSON
	for (int i = 0; i < numOfSprites; i++) {
		framesPerSprite[i] = 4;
	}

	//std::cout << filePath << ": " << numOfSprites << std::endl;
}

void Animation::LoadDynamic(std::string filePath) {
	int spriteCount = 0;
	std::string filename = "";

	filePath += animName + "/";
	for (int i = 0;; i++) {
		filename = filePath + std::to_string(spriteCount++) + ".png";
		sf::Texture* newTexture = new sf::Texture();
		if (!newTexture->loadFromFile(filename)) {
			break;
		}

		textureList.push_back(*newTexture);
	}
	numOfSprites = --spriteCount;

	// SETUP THE SPRITES WITH THE TEXTURES
	spriteList = new sf::Sprite[numOfSprites]; // Might need to initialize them all to nullptr first

	for (int i = 0; i < numOfSprites; i++) {
		spriteList[i].setTexture(textureList[i]);
		spriteList[i].setOrigin(textureList[i].getSize().x * 0.5f, textureList[i].getSize().y * 0.5f); // Set the Origin to the Center of the Texture, all frames should have the same size sprite
	}

	framesPerSprite = new int[numOfSprites];
	for (int i = 0; i < numOfSprites; i++) {
		framesPerSprite[i] = 2;
	}

	currentSprite = spriteList[0];

	framesPerSprite = new int[numOfSprites];

	//////////////////// SETUP HOW MANY FRAMES EACH SPRITE IS OUT FOR
	// WILL EVENTUALLY USE JSON
	for (int i = 0; i < numOfSprites; i++) {
		framesPerSprite[i] = 4;
	}

	return;
}

// CONSIDER DOING A TEMPLATE FOR THIS
void Animation::Update() {
	// Generic anim update for animations with no new owner, no new scale, no new position
	currentSprite = spriteList[currentSpriteIndex];

	currentSprite.setPosition(position);
	currentSprite.setScale(sf::Vector2f(xScale, currentSprite.getScale().y));

	currentSpriteFrame++;
	if (currentSpriteFrame >= framesPerSprite[currentSpriteIndex])
	{
		currentSpriteFrame = 0;
		currentSpriteIndex++;

		if (currentSpriteIndex >= numOfSprites)
		{
			if (looping) {
				if (-1 >= numOfLoops || currentLoop < numOfLoops) {
					currentSpriteIndex = 0;
					currentLoop++;
					RestoreFrameFunctionQueue();
					return;
				}
			}

			isDone = true;
			currentSpriteIndex = numOfSprites - 1;
		}
	}
}

// CONSIDER DOING A TEMPLATE FOR THIS
void Animation::Update(sf::Vector2f newPosition, int newXScale, Fighter* animOwner) {
	// CONSIDER COMING UP WITH A BETTER SOLUTION TO MULTI FUNCTIONS ON SAME FRAME
	// BECASUE INFINITE LOOP IS UGHHGHGHGH
	bool loop = true;
	while (loop) {
		loop = CheckFrameFunctionQueue(animOwner);
		CheckHurtBoxesQueue();
		CheckHitBoxesQueue();
		CheckBoundBoxQueue();
	}

	currentSprite = spriteList[currentSpriteIndex];

	position = newPosition;
	currentSprite.setPosition(position);

	xScale = newXScale;
	currentSprite.setScale(sf::Vector2f(xScale, currentSprite.getScale().y));

	UpdateBoundBox(position, xScale);
	UpdateHitBox(position, xScale);
	UpdateHurtBoxes(position, xScale);

	currentSpriteFrame++;
	if (currentSpriteFrame >= framesPerSprite[currentSpriteIndex])
	{
		currentSpriteFrame = 0;
		currentSpriteIndex++;

		if (currentSpriteIndex >= numOfSprites)
		{
			if (looping) {
				if (-1 >= numOfLoops || currentLoop < numOfLoops) {
					currentSpriteIndex = 0;
					currentLoop++;
					RestoreFrameFunctionQueue();
					return;
				}
			}

			isDone = true;
			currentSpriteIndex = numOfSprites - 1;
		}
	}
}

// CONSIDER DOING A TEMPLATE FOR THIS
void Animation::Update(sf::Vector2f newPosition, int newXScale, Projectile* animOwner) {

	// CONSIDER COMING UP WITH A BETTER SOLUTION TO MULTI FUNCTIONS ON SAME FRAME
	// BECASUE INFINITE LOOP IS UGHHGHGHGH
	bool loop = true;
	while (loop) {
		loop = CheckFrameFunctionQueue(animOwner);
		CheckHurtBoxesQueue();
		CheckHitBoxesQueue();
		CheckBoundBoxQueue();
	}

	currentSprite = spriteList[currentSpriteIndex];

	position = newPosition;
	currentSprite.setPosition(position);
	xScale = newXScale;
	currentSprite.setScale(sf::Vector2f(xScale, currentSprite.getScale().y));

	UpdateBoundBox(position, xScale);
	UpdateHitBox(position, xScale);
	UpdateHurtBoxes(position, xScale);

	currentSpriteFrame++;
	if (currentSpriteFrame >= framesPerSprite[currentSpriteIndex])
	{
		currentSpriteFrame = 0;
		currentSpriteIndex++;

		if (currentSpriteIndex >= numOfSprites)
		{
			if (looping) {
				if (-1 >= numOfLoops || currentLoop < numOfLoops) {
					currentSpriteIndex = 0;
					currentLoop++;
					RestoreFrameFunctionQueue();
					return;
				}
			}
			isDone = true;
			currentSpriteIndex = numOfSprites - 1;
		}
	}
}


void Animation::ReUpdateBoxes(sf::Vector2f position, int xScale) {
	currentSprite.setPosition(position);

	CheckHurtBoxesQueue();
	CheckHitBoxesQueue();
	CheckBoundBoxQueue();

	UpdateBoundBox(position, xScale);
	UpdateHitBox(position, xScale);
	UpdateHurtBoxes(position, xScale);
}



void Animation::Draw(sf::RenderWindow* window, sf::Color hue) {
	currentSprite.setColor(hue);
	window->draw(currentSprite);
}

void Animation::Draw(sf::RenderWindow* window, sf::Shader& shader) {
	window->draw(currentSprite, &shader);
}

void Animation::SetLooping(bool loop) {
	looping = loop;
}

bool Animation::IsDone() {
	return isDone;
}

void Animation::SetFramesPerSprite(int* frames) {
	delete framesPerSprite;
	framesPerSprite = frames;
}

void Animation::SetFramesAtSprite(int index, int numOfFrames) {
	if (index > numOfSprites)
		return;

	framesPerSprite[index] = numOfFrames;
}

void Animation::SetFramesOfLastSprite(int frames) {
	framesPerSprite[numOfSprites-1] = frames;
}


void Animation::SetFramesOfAnimation(int frames) {
	int remainder = frames % numOfSprites;
	for (int i = 0; i < numOfSprites; i++) {
		framesPerSprite[i] = frames / numOfSprites;
	}

	if (0 < remainder) {
		for (int i = 0; remainder > 0; i++, remainder--) {
			framesPerSprite[i] += 1;
		}
	}
}

void Animation::Restart() {
	isDone = false;
	currentSpriteIndex = 0;
	currentSpriteFrame = 0;
}


void Animation::AddFrameFunction(int frame, int frameEnum) {
	frameFunctionQueue.push(std::make_pair(frame, frameEnum));
}

bool Animation::CheckFrameFunctionQueue(Fighter* animOwner) {
	if (!frameFunctionQueue.empty() && frameFunctionQueue.front().first == currentSpriteIndex && (currentSpriteFrame == 0)) {
		animOwner->CallEnumFunction(frameFunctionQueue.front().second);
		usedFrameFunctionQueue.push(frameFunctionQueue.front());
		frameFunctionQueue.pop();
		return true;
	}
	else
		return false;
}

bool Animation::CheckFrameFunctionQueue(Projectile* animOwner) {
	if (!frameFunctionQueue.empty() && frameFunctionQueue.front().first == currentSpriteIndex && (currentSpriteFrame == 0)) {
		animOwner->CallEnumFunction(frameFunctionQueue.front().second);
		usedFrameFunctionQueue.push(frameFunctionQueue.front());
		frameFunctionQueue.pop();
		return true;
	}
	else
		return false;
}

void Animation::RestoreFrameFunctionQueue() {
	while (!usedFrameFunctionQueue.empty()) {
		frameFunctionQueue.push(usedFrameFunctionQueue.front());
		usedFrameFunctionQueue.pop();
	}
}

void Animation::AddHurtBoxes(int frame, std::vector<sf::IntRect> hurtBoxes) {
	hurtBoxesQueue.push(std::make_pair(frame, hurtBoxes));
}

std::vector<sf::IntRect> Animation::GetHurtBoxes() {
	return hurtBoxesActual;
}

bool Animation::CheckHurtBoxesQueue() {
	if (!hurtBoxesQueue.empty() && hurtBoxesQueue.front().first == currentSpriteIndex && (currentSpriteFrame == 0)) {
		hurtBoxesValues = hurtBoxesQueue.front().second;
		hurtBoxesActual = hurtBoxesValues;
		hurtBoxesQueue.pop();
		return true;
	}
	else
		return false;
}

void Animation::UpdateHurtBoxes(sf::Vector2f position, int xScale) {
	for (int i = 0; i < hurtBoxesActual.size(); i++) {
		hurtBoxesActual[i].top = (currentSprite.getPosition().y - currentSprite.getOrigin().y) + hurtBoxesValues[i].top;
		hurtBoxesActual[i].width = hurtBoxesValues[i].width;
		hurtBoxesActual[i].height = hurtBoxesValues[i].height;

		if (0 < xScale)
			hurtBoxesActual[i].left = (currentSprite.getPosition().x - currentSprite.getOrigin().x) + hurtBoxesValues[i].left;
		else
			hurtBoxesActual[i].left = (currentSprite.getPosition().x + currentSprite.getOrigin().x) - (hurtBoxesValues[i].left + hurtBoxesValues[i].width);
	}
}

void Animation::AddHitBox(int frame, sf::IntRect hitBox) {
	hitBoxQueue.push(std::make_pair(frame, hitBox));
}

sf::IntRect Animation::GetHitBox() {
	return hitBoxActual;
}

bool Animation::CheckHitBoxesQueue() {
	if (!hitBoxQueue.empty() && hitBoxQueue.front().first == currentSpriteIndex && (currentSpriteFrame == 0)) {
		hitBoxValues = hitBoxQueue.front().second;
		hitBoxQueue.pop();
		return true;
	}
	else
		return true;
}

void Animation::UpdateHitBox(sf::Vector2f position, int xScale) {
	hitBoxActual.top = (currentSprite.getPosition().y - currentSprite.getOrigin().y) + hitBoxValues.top;
	hitBoxActual.width = hitBoxValues.width;
	hitBoxActual.height = hitBoxValues.height;

	if (0 < xScale)
		hitBoxActual.left = (currentSprite.getPosition().x - currentSprite.getOrigin().x) + hitBoxValues.left;
	else
		hitBoxActual.left = (currentSprite.getPosition().x + currentSprite.getOrigin().x) - (hitBoxValues.left + hitBoxValues.width);
}

void Animation::AddBoundBox(int frame, sf::IntRect boundBox) {
	boundBoxQueue.push(std::make_pair(frame, boundBox));
}

sf::IntRect Animation::GetBoundBox() {
	return boundBoxActual;
}

std::string Animation::GetName() {
	return animName;
}

std::string Animation::GetAnimToPlayWhenDone() {
	return animToPlayWhenDone;
}

bool Animation::CheckBoundBoxQueue() {
	if (!boundBoxQueue.empty() && boundBoxQueue.front().first == currentSpriteIndex && (currentSpriteFrame == 0)) {
		boundBoxValues = boundBoxQueue.front().second;
		boundBoxQueue.pop();
		return true;
	}
	else
		return false;
}

bool Animation::CheckDamageInfoQueue() {
	if (!damageInfoQueue.empty() && damageInfoQueue.front().first == currentSpriteIndex && 0 == currentSpriteFrame) {
		damageInfo = damageInfoQueue.front().second;
		damageInfoQueue.pop();
		return true;
	}
	else
	return false;
}

void Animation::UpdateBoundBox(sf::Vector2f position, int xScale) {
	boundBoxActual.top = (currentSprite.getPosition().y - currentSprite.getOrigin().y) + boundBoxValues.top;
	boundBoxActual.width = boundBoxValues.width;
	boundBoxActual.height = boundBoxValues.height;

	if (0 < xScale)
		boundBoxActual.left = (currentSprite.getPosition().x - currentSprite.getOrigin().x) + boundBoxValues.left;
	else
		boundBoxActual.left = (currentSprite.getPosition().x + currentSprite.getOrigin().x) - (boundBoxValues.left + boundBoxValues.width);
}

sf::IntRect Animation::CheckNextBoundBox(sf::Vector2f position, int xScale) {
	sf::IntRect nextBoundBox = boundBoxActual;

	nextBoundBox.top = (currentSprite.getPosition().y - currentSprite.getOrigin().y) + boundBoxValues.top;

	if (0 < xScale)
		nextBoundBox.left = (currentSprite.getPosition().x - currentSprite.getOrigin().x) + boundBoxValues.left;
	else
		nextBoundBox.left = (currentSprite.getPosition().x + currentSprite.getOrigin().x) - (boundBoxValues.left + boundBoxValues.width);

	return nextBoundBox;
}

void Animation::SetPosition(sf::Vector2f newPosition) {
	position = newPosition;
	currentSprite.setPosition(position);
}

void Animation::SetXScale(int newXScale) {
	xScale = newXScale;
	currentSprite.setScale(sf::Vector2f(xScale, currentSprite.getScale().y));
}

void Animation::SetNumOfLoops(int numberOfLoops) {
	numOfLoops = numberOfLoops;
}

void Animation::SetOrigin(Origin newOrigin) {
	sf::Vector2f origin;

	switch (newOrigin) {
	case Origin::top_left:
		origin = sf::Vector2f(0, 0);
		break;
	case Origin::top_center:
		origin = sf::Vector2f(textureList[0].getSize().x * 0.5f, 0);
		break;
	case Origin::top_right:
		origin = sf::Vector2f(textureList[0].getSize().x, 0);
		break;
	case Origin::left_center:
		origin = sf::Vector2f(0, textureList[0].getSize().y * 0.5f);
		break;
	case Origin::center:
		origin = sf::Vector2f(textureList[0].getSize().x * 0.5f, textureList[0].getSize().y * 0.5f);
		break;
	case Origin::right_center:
		origin = sf::Vector2f(textureList[0].getSize().x, textureList[0].getSize().y * 0.5f);
		break;
	case Origin::bottom_left:
		origin = sf::Vector2f(0, textureList[0].getSize().y);
		break;
	case Origin::bottom_center:
		origin = sf::Vector2f(textureList[0].getSize().x * 0.5f, textureList[0].getSize().y);
		break;
	case Origin::bottom_right:
		origin = sf::Vector2f(textureList[0].getSize().x, textureList[0].getSize().y);
		break;
	}

	for (int i = 0; i < numOfSprites; i++) {
		spriteList[i].setOrigin(origin); // Set the Origin to the Center of the Texture, all frames should have the same size sprite
	}
}

void Animation::AddDamageInfo(DamageInfo* dInfo) {
	damageInfo = dInfo;
}

void Animation::AddDamageInfoToQueue(int spriteIndex, DamageInfo* dInfo) {
	damageInfoQueue.push(std::make_pair(spriteIndex, dInfo));
}

DamageInfo Animation::GetDamageInfo() {
	DamageInfo dInfo;

	if (damageInfo)
		dInfo = *damageInfo;

	return dInfo;
}

sf::Vector2f Animation::GetOrigin() {
	return currentSprite.getOrigin();
}

void Animation::AdvanceOneSprite() {
	if (disableSpriteAdvancement || currentSpriteIndex == (numOfSprites - 1))
		return;

	currentSpriteIndex++;
	currentSpriteFrame = 0;
}

// Debug
int Animation::DebugGetCurrentSpriteIndex() {
	return currentSpriteIndex;
}

int Animation::DebugGetCurrentSpriteFrame() {
	return currentSpriteFrame;
}

void Animation::SetDisablSpriteAdvancement(bool setting) {
	disableSpriteAdvancement = setting;
}

void Animation::EnableDebug() {
	debug = true;
}
