#include "CrossCutter.h"

#include <iostream>

CrossCutter::CrossCutter() {
	name = CROSS_CUTTER;
}

CrossCutter::~CrossCutter() {
}

void CrossCutter::Load() {
	std::string charPath = "Textures/Chars/Kyosuke/Projectiles/" + name + "/";

	spawnOffset = sf::Vector2f(86.f, 60.f);
	SetMaxDurability(1);

	Animation* temp;
	int* framesPerSprite;

	temp = new Animation(charPath, END, 8, false);
	temp->SetFramesOfAnimation(16);
	temp->AddFrameFunction(0, cross_cutter_2);
	temp->AddDamageInfo(new DamageInfo(70000, 1, 20, 31, 0, 1, sf::Vector2f(1.f, 0.f), DamageScale::SpecialScale, HitSparkType::Heavy));
	temp->AddHitBox(0, sf::IntRect(70, 68, 22, 18));
	animManager.AddAnimation(END, temp);
	destroyOnAnim = END;

	temp = new Animation(charPath, HIT, 8, false);
	animManager.AddAnimation(HIT, temp);
	altDestroyOnAnim = HIT;

	if (1 == yScale)
		charPath += "Up/";
	else
		charPath += "Down/";

	temp = new Animation(charPath, START, 12, false, MIDDLE);
	temp->SetFramesOfAnimation(24);
	temp->AddDamageInfo(new DamageInfo(10468, 1, 20, 31, 0, 1, sf::Vector2f(1.f, 0.f), DamageScale::SpecialScale, HitSparkType::Heavy));
	temp->AddHitBox(0, sf::IntRect(76, 73, 16, 15));
	animManager.AddAnimation(START, temp);

	temp = new Animation(charPath, MIDDLE, 12, false, END);
	temp->SetFramesOfAnimation(24);
	temp->AddFrameFunction(0, cross_cutter_1);
	temp->AddDamageInfo(new DamageInfo(10468, 1, 20, 31, 0, 1, sf::Vector2f(1.f, 0.f), DamageScale::SpecialScale, HitSparkType::Heavy));
	temp->AddHitBox(0, sf::IntRect(76, 73, 16, 15));
	animManager.AddAnimation(MIDDLE, temp);

	animManager.Play(START, position, xScale);
}

void CrossCutter::Update() {
	if (hasHitMain || hasHitSupport) {
		velocity.x = 0;
		velocity.y = 0;
		animManager.Play(HIT, position, xScale);
	}

	Projectile::Update();
}

void CrossCutter::SetYScale(float newYScale) {
	yScale = newYScale;
}

bool CrossCutter::CallEnumFunction(int functionEnum) {

	if (Projectile::CallEnumFunction(functionEnum))
		return false;

	switch (functionEnum) {
	case cross_cutter_1:
		CrossCutter1();
		return true;
	case cross_cutter_2:
		CrossCutter2();
		return true;
	case cross_cutter_3:
		CrossCutter3();
		return true;
	default:
		std::cout << "Function: " << functionEnum << " not found" << std::endl;
		break;
	}

	return false;
}

void CrossCutter::CrossCutter1() {
	velocity.y *= -1;
}

void CrossCutter::CrossCutter2() {
	velocity.y = 0;
	velocity.x = 5.f * xScale;
}

void CrossCutter::CrossCutter3() {
}