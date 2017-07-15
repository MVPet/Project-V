#include "SakiBeam.h"

SakiBeam::SakiBeam() {
	name = SAKI_BEAM;
}

SakiBeam::~SakiBeam() {
}

void SakiBeam::Load() {
	std::string charPath = "Textures/Chars/Saki/Projectiles/" + name + "/";

	spawnOffset = sf::Vector2f(250.f, 0.f);

	Animation* temp;
	int* framesPerSprite;

	temp = new Animation(charPath, IDLE, 14, false);
	temp->SetFramesOfAnimation(28);
	temp->AddDamageInfo(new DamageInfo(10468, 0, 5, 5, 0, 2, sf::Vector2f(1.5f, 0.f), DamageScale::SpecialScale, HitSparkType::Light));
	temp->AddFrameFunction(2, reset_has_hit);
	temp->AddFrameFunction(5, reset_has_hit);
	temp->AddFrameFunction(8, reset_has_hit);
	temp->AddHitBox(0, sf::IntRect(0, 0, 640, 70));
	temp->AddBoundBox(0, sf::IntRect(0, 0, 0, 0));
	animManager.AddAnimation(IDLE, temp);
	destroyOnAnim = IDLE;

	// Play default animation
	animManager.Play(IDLE, position, xScale);
}