#include "Hadouken.h"
#include <iostream>

Hadouken::Hadouken() {
	name = HADOUKEN;
}

Hadouken::~Hadouken() {
}

void Hadouken::Load() {
	std::string charPath = "Textures/Chars/Ryu/Projectiles/" + name + "/";

	spawnOffset = sf::Vector2f(20.f, 59.f);
	lifeLimit = 600.f;
	SetMaxDurability(2);

	Animation* temp;
	int* framesPerSprite;

	temp = new Animation(charPath, IDLE, 8, true);
	framesPerSprite = new int[8]{ 2, 2, 2, 2, 2, 2, 2, 2 };
	temp->SetFramesPerSprite(framesPerSprite);
	std::cout << OCRAM << std::endl;
	temp->AddDamageInfo(new DamageInfo(100000, 800, 33, 31, 0, 1, sf::Vector2f(1.5f, 0.f), DamageScale::SpecialScale, HitSparkType::Medium));
	temp->AddHitBox(0, sf::IntRect(44, 40, 59, 42));
	temp->AddBoundBox(0, sf::IntRect(0,0,0,0));
	animManager.AddAnimation(IDLE, temp);

	temp = new Animation(charPath, HIT, 6, false);
	framesPerSprite = new int[6]{ 2, 2, 2, 2, 2, 2 };
	temp->SetFramesPerSprite(framesPerSprite);
	animManager.AddAnimation(HIT, temp);
	destroyOnAnim = HIT;

	// Play default animation
	animManager.Play(IDLE, position, xScale);
}

void Hadouken::Update() {
	if (hasHitMain || hasHitSupport || noDurability) {
		velocity.x = 0;
		velocity.y = 0;
		animManager.Play(HIT, position, xScale);
	}

	Projectile::Update();
}