#include "ShadowWave.h"

ShadowWave::ShadowWave() {
	name = SHADOW_WAVE;
}

ShadowWave::~ShadowWave() {
}

void ShadowWave::Load() {
	std::string charPath = "Textures/Chars/Kyosuke/Projectiles/" + name + "/";

	spawnOffset = sf::Vector2f(0.f, 0.f);

	Animation* temp;
	int* framesPerSprite;

	temp = new Animation(charPath, IDLE, 13, false);
	temp->SetFramesOfAnimation(13);
	temp->AddDamageInfo(new DamageInfo(70000, 800, 33, 31, 0, 1, sf::Vector2f(2.5f, 4.f), DamageScale::SpecialScale, HitSparkType::Nothing));
	temp->AddHitBox(2, sf::IntRect(185, 181, 86, 52));
	temp->AddHitBox(5, sf::IntRect(0, 0, 0, 0));
	animManager.AddAnimation(IDLE, temp);
	destroyOnAnim = IDLE;

	animManager.Play(IDLE, position, xScale);
}