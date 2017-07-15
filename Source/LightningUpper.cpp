#include "LightningUpper.h"

LightningUpper::LightningUpper() {
	name = LIGHTNING_UPPER;
}

LightningUpper::~LightningUpper() {
}

void LightningUpper::Load() {
	std::string charPath = "Textures/Chars/Kyosuke/Projectiles/" + name + "/";

	spawnOffset = sf::Vector2f(0.f, 0.f);

	Animation* temp;
	int* framesPerSprite;

	temp = new Animation(charPath, IDLE, 14, false);
	temp->SetFramesOfAnimation(14);
	temp->AddDamageInfo(new DamageInfo(80000, 800, 40, 31, 4, 1, sf::Vector2f(0.f, -10.f), DamageScale::SpecialScale, HitSparkType::Heavy, false, AdditionalEffect::OTG));
	temp->AddHitBox(4, sf::IntRect(167, 237, 68, 55));
	temp->AddHitBox(5, sf::IntRect(0, 0, 0, 0));
	animManager.AddAnimation(IDLE, temp);
	destroyOnAnim = IDLE;

	animManager.Play(IDLE, position, xScale);
}