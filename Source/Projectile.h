#pragma once

#include <SFML\Graphics.hpp>

#include "Fighter.h"
#include "AnimationManager.h"

using DamageScale = DamageInfo::DamageScale;
using HitSparkType = DamageInfo::HitSparkType;

class Projectile {
public:
	Projectile();
	~Projectile();

	virtual void Update();
	virtual void Load();
	virtual void Draw(sf::RenderWindow* window);

	std::string GetName();

	void SetXScale(int scale);
	void SetPosition(sf::Vector2f newPosition);
	void SetVelocity(sf::Vector2f newVelocity);
	bool IsItTimeToDestroy();

	bool CheckEnemyCollision(Fighter* owner, Fighter* enemy);
	void CheckEnemyProjectileCollision(Fighter* enemy);
	void ReduceDurability(int damage);
	int GetDurability();

	virtual bool CallEnumFunction(int functionEnum);

	//void AddAnimation(std::string animName, Animation* anim, bool destroyAtEnd);

protected:
	enum EnumFunctions
	{
		reset_has_hit, last,
	};

	void SetMaxDurability(int value);

	AnimationManager  animManager;

	float xScale = 1;
	int maxDurability = 999;
	int durability = 1;
	bool noDurability = false;
	bool destroyNow = false;
	//bool hasHit = false;
	bool hasHitMain = false;
	bool hasHitSupport = false;
	//bool destroyAtEnd = false;
	std::string destroyOnAnim = "";
	std::string altDestroyOnAnim = "";
	float lifeLimit = 9999.f;
	float lifeTime = 0.f;
	sf::Vector2f spawnOffset;
	sf::Vector2f position;
	sf::Vector2f velocity;
	std::string name;
};