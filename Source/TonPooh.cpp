#include "TonPooh.h"
#include "Controls.h"
#include "Fight.h"

#include <iostream>

using AdditionalEffect = DamageInfo::AdditionalEffect;

TonPooh::TonPooh() {
}

TonPooh::~TonPooh() {
}

void TonPooh::Load() {
	//std::string name = TON_POOH;
	name = TON_POOH;
	std::string charPath = "Textures/Chars/" + name + "/";
	isPlayable = false;
	center = sf::Vector2f(60, 52);
	maxHealth = 1;
	maxSpeed = 0.f;

	Animation* temp;
	DamageInfo* dInfo;
	std::vector<sf::IntRect> hurtBoxes;
	int* framesPerSprite;

	// IDLE
	temp = new Animation(charPath, IDLE, 1, true);
	animManager.AddAnimation(IDLE, temp);

	// SUPPORT IDLE
	temp = new Animation(charPath, IDLE, 1, true);
	animManager.AddAnimation(SUPPORT_IDLE, temp);


	// FALLING
	temp = new Animation(charPath, FALLING, 1, true);
	temp->AddFrameFunction(0, reset_to_idle);
	temp->AddBoundBox(0, sf::IntRect(208, 17, 45, 63));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(182, 16, 73, 33));
	hurtBoxes.push_back(sf::IntRect(209, 47, 87, 34));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(FALLING, temp);

	// SUPPORT ENTER
	temp = new Animation(charPath, SUPPORT_ENTER, 1, true);
	temp->AddBoundBox(0, sf::IntRect(214, 20, 51, 65));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(199, 20, 74, 51));
	hurtBoxes.push_back(sf::IntRect(251, 67, 46, 35));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(SUPPORT_ENTER, temp);

	// SUPPORT
	temp = new Animation(charPath, SUPPORT, 11, false);
	temp->AddDamageInfo(new DamageInfo(100000, 0, 7, 7, 6, 1, sf::Vector2f(1.5f, 0.f), DamageScale::MediumScale, HitSparkType::Medium, false, AdditionalEffect::Knockdown, sf::Vector2f(2.f, -5.f)));
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(0, do_support_attack);
	temp->SetFramesOfAnimation(44);
	temp->AddBoundBox(0, sf::IntRect(214, 6, 50, 86));
	temp->AddHitBox(3, sf::IntRect(189, 12, 237, 67));
	temp->AddHitBox(5, sf::IntRect(0, 0, 0, 0));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(202, 8, 78, 54));
	hurtBoxes.push_back(sf::IntRect(196, 60, 37, 35));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(220, 8, 39, 41));
	hurtBoxes.push_back(sf::IntRect(239, 28, 39, 68));
	temp->AddHurtBoxes(1, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(205, 8, 53, 55));
	hurtBoxes.push_back(sf::IntRect(247, 61, 32, 38));
	temp->AddHurtBoxes(2, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(186, 8, 118, 54));
	hurtBoxes.push_back(sf::IntRect(196, 60, 37, 35));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(205, 8, 53, 55));
	hurtBoxes.push_back(sf::IntRect(219, 61, 54, 30));
	temp->AddHurtBoxes(9, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(202, 8, 54, 54));
	hurtBoxes.push_back(sf::IntRect(219, 60, 60, 35));
	temp->AddHurtBoxes(10, hurtBoxes);
	animManager.AddAnimation(SUPPORT, temp);

	// SUPPORT END
	temp = new Animation(charPath, SUPPORT_END, 3, false, SUPPORT_EXIT);
	temp->AddBoundBox(0, sf::IntRect(205, 27, 42, 50));
	animManager.AddAnimation(SUPPORT_END, temp);

	// SUPPORT EXIT
	temp = new Animation(charPath, SUPPORT_EXIT, 1, true);
	temp->AddFrameFunction(0, do_support_exit);
	temp->AddBoundBox(0, sf::IntRect(224, 15, 50, 73));
	animManager.AddAnimation(SUPPORT_EXIT, temp);

	Fighter::Load();
}

void TonPooh::UpdateAnimations() {
	Fighter::UpdateAnimations();
}

bool TonPooh::CallEnumFunction(int functionEnum) {

	if (Fighter::CallEnumFunction(functionEnum))
		return false;

	switch (functionEnum) {
	case do_support_attack:
		DoSupportAttack();
		return true;
	default:
		std::cout << "Function: " << functionEnum << " not found" << std::endl;
		return false;
	}
}

void TonPooh::DoSupportAttack() {
	inAir = true;
	SetCustomGravity(GRAVITY_CONST * 0.5f);

	velocity.x = 2.f * xScale;
	velocity.y = -7.f;
}

void TonPooh::SetColor(int colorNum) {
	if (2 == colorNum) {
		colorShader.setParameter("texture", sf::Shader::CurrentTexture);
		colorShader.setParameter("color1", 0.690f, 0.690f, 0.690f);
		colorShader.setParameter("replace1", 0.188f, 0.188f, 0.188f);
		colorShader.setParameter("color2", 0.564f, 0.564f, 0.564f);
		colorShader.setParameter("replace2", 0.125f, 0.125f, 0.125f);
		colorShader.setParameter("color3", 0.313f, 0.313f, 0.313f);
		colorShader.setParameter("replace3", 0.f, 0.f, 0.f);
		colorShader.setParameter("color4", 0.878f, 0.878f, 0.878f);
		colorShader.setParameter("replace4", 0.313f, 0.313f, 0.313f);
		colorShader.setParameter("color5", 0.752f, 0.752f, 0.752f);
		colorShader.setParameter("replace5", 0.250f, 0.250f, 0.250f);
		colorShader.setParameter("color6", 0.941f, 0.941f, 0.941f);
		colorShader.setParameter("replace6", 0.627f, 0.627f, 0.627f);
		colorShader.setParameter("color7", 0.439f, 0.439f, 0.439f);
		colorShader.setParameter("replace7", 0.062f, 0.062f, 0.062f);
	}
}