#include "SuperLightningUpper.h"

SuperLightningUpper::SuperLightningUpper() {
	name = SUPER_LIGHTNING_UPPER;
}

SuperLightningUpper::~SuperLightningUpper() {
}

void SuperLightningUpper::Load() {
	std::string charPath = "Textures/Chars/Kyosuke/Projectiles/" + name + "/";

	spawnOffset = sf::Vector2f(0.f, 0.f);

	Animation* temp;
	int* framesPerSprite;

	temp = new Animation(charPath, IDLE, 20, false);
	temp->SetFramesOfAnimation(40);
	temp->AddFrameFunction(4, reset_has_hit);
	temp->AddFrameFunction(6, reset_has_hit);
	temp->AddFrameFunction(8, reset_has_hit);
	temp->AddFrameFunction(10, reset_has_hit);
	temp->AddDamageInfo(new DamageInfo(60000, 800, 33, 31, 0, 6, sf::Vector2f(3.f, -7.f), DamageScale::SpecialScale, HitSparkType::Heavy, false, AdditionalEffect::OTG));
	temp->AddHitBox(2, sf::IntRect(273, 208, 93, 175));
	animManager.AddAnimation(IDLE, temp);
	destroyOnAnim = IDLE;

	animManager.Play(IDLE, position, xScale);
}