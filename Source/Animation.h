#pragma once

#include <string>
#include <queue>
#include <utility>
#include <vector>

#include <SFML\Graphics.hpp>

#include "DamageInfo.h"

class Fighter;
class Projectile;

class Animation
{
public:
	enum Origin{
		top_left, top_center, top_right, left_center, center, right_center, bottom_left, bottom_center, bottom_right,
	};

	Animation();
	Animation(std::string filePath, std::string name, int totalFrames, bool loop, std::string nextAnimToPlay = "", int numberOfLoops = -1);
	~Animation();

	// CONSIDER DOING A TEMPLATE FOR THIS
	void Update();
	void Update(sf::Vector2f newPosition, int newXScale, Fighter* animOwner); // Called once per frame (should be 60fps)
	void Update(sf::Vector2f newPosition, int newXScale, Projectile* animOwner); // Called once per frame (should be 60fps)
	void ReUpdateBoxes(sf::Vector2f position, int xScale);

	void Load(std::string animName);
	void LoadDynamic(std::string animName);
	void Draw(sf::RenderWindow* window, sf::Shader& shader);
	void Draw(sf::RenderWindow* window, sf::Color hue);
	void AdvanceOneSprite();

	void AddFrameFunction(int frame, int functionEnum);
	void AddBoundBox(int frame, sf::IntRect boundBox);
	void AddHurtBoxes(int frame, std::vector<sf::IntRect> hurtBoxes);
	void AddHitBox(int frame, sf::IntRect hitBox);
	void SetFramesAtSprite(int index, int numOfFrames);
	void SetFramesPerSprite(int* frames);
	void SetFramesOfAnimation(int frames);
	void SetFramesOfLastSprite(int frames);
	void AddDamageInfo(DamageInfo* dInfo);
	void AddDamageInfoToQueue(int spriteIndex, DamageInfo* dInfo);
	DamageInfo GetDamageInfo();
	//void AddGuardBox(int frame, sf::IntRect guardBox);

	void SetLooping(bool loop);

	sf::IntRect GetBoundBox();
	sf::IntRect CheckNextBoundBox(sf::Vector2f position, int xScale);
	sf::IntRect GetHitBox();
	std::vector<sf::IntRect> GetHurtBoxes();
	std::string GetName();
	std::string GetAnimToPlayWhenDone();
	sf::Vector2f GetOrigin();

	void SetPosition(sf::Vector2f newPosition);
	void SetXScale(int newXScale);
	void SetNumOfLoops(int numberOfLoops);
	void SetOrigin(Origin newOrigin);
	void SetDisablSpriteAdvancement(bool setting);
	void EnableDebug();

	bool IsDone();

	void Restart();

	// DEBUG STUFF
	int DebugGetCurrentSpriteIndex();
	int DebugGetCurrentSpriteFrame();

private:

	// CONSIDER DOING A TEMPLATE FOR THIS
	bool CheckFrameFunctionQueue(Fighter* animOwner);
	bool CheckFrameFunctionQueue(Projectile* animOwner);
	void RestoreFrameFunctionQueue();

	void UpdateHurtBoxes(sf::Vector2f position, int xScale);
	bool CheckHurtBoxesQueue();
	void UpdateHitBox(sf::Vector2f position, int xScale);
	bool CheckHitBoxesQueue();
	void UpdateBoundBox(sf::Vector2f position, int xScale);
	bool CheckBoundBoxQueue();

	bool CheckDamageInfoQueue();

	int numOfSprites;
	int currentSpriteFrame = 0;
	int currentSpriteIndex = 0;
	int currentLoop = 0;
	bool looping = false;
	int numOfLoops = 0;
	bool isDone = false;
	bool disableSpriteAdvancement = false;
	bool debug = false;

	sf::Vector2f position;
	int xScale = 1;

	std::string animToPlayWhenDone;
	std::string animName;

	sf::Sprite currentSprite;
	sf::Sprite* spriteList;
	//sf::Texture* textureList;
	std::vector<sf::Texture> textureList;
	int* framesPerSprite;
	sf::IntRect boundBoxValues;
	sf::IntRect boundBoxActual;
	std::queue<std::pair<int, sf::IntRect>> boundBoxQueue;

	std::vector<sf::IntRect> hurtBoxesActual;
	std::vector<sf::IntRect> hurtBoxesValues;
	std::queue<std::pair<int, std::vector<sf::IntRect>>> hurtBoxesQueue;

	DamageInfo* damageInfo;
	std::queue<std::pair<int, DamageInfo*>> damageInfoQueue;

	sf::IntRect hitBoxValues;
	sf::IntRect hitBoxActual;
	std::queue<std::pair<int, sf::IntRect>> hitBoxQueue;
	//sf::IntRect guardBoxValues;
	//sf::IntRect guardBoxActual;
	//std::queue<std::pair<int, sf::IntRect>> guardBoxQueue;
	std::queue<std::pair<int, int>> frameFunctionQueue;
	std::queue<std::pair<int, int>> usedFrameFunctionQueue;
};