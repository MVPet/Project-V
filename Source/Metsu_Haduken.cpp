#include "Metsu_Haduken.h"

#include <iostream>

MetsuHadouken::MetsuHadouken() {
	name = METSU_HADOUKEN;
}

MetsuHadouken::~MetsuHadouken() {
}

void MetsuHadouken::Load() {
	std::string charPath = "Textures/Chars/Ryu/Projectiles/" + name + "/";

	spawnOffset = sf::Vector2f(390.f, 59.f);

	Animation* temp;
	int* framesPerSprite;

	temp = new Animation(charPath, START, 6, false, MIDDLE);
	framesPerSprite = new int[6]{ 1, 1, 1, 1, 1, 1 };
	temp->SetFramesPerSprite(framesPerSprite);
	animManager.AddAnimation(START, temp);

	temp = new Animation(charPath, MIDDLE, 2, true, END, 20);
	temp->AddDamageInfo(new DamageInfo(10468, 1, 20, 31, 0, 1, sf::Vector2f(5.f, 0.f), DamageScale::SpecialScale, HitSparkType::Heavy, true));
	framesPerSprite = new int[2]{ 2, 2 };
	temp->SetFramesPerSprite(framesPerSprite);
	temp->AddFrameFunction(1, reset_has_hit);
	temp->AddHitBox(0, sf::IntRect(0, 0, 640, 70));
	temp->AddBoundBox(0, sf::IntRect(0, 0, 0, 0));
	animManager.AddAnimation(MIDDLE, temp);

	temp = new Animation(charPath, END, 7, false);
	framesPerSprite = new int[7]{ 1, 1, 1, 1, 1, 1, 1 };
	temp->SetFramesPerSprite(framesPerSprite);
	animManager.AddAnimation(END, temp);
	destroyOnAnim = END;

	animManager.Play(START, position, xScale);
}