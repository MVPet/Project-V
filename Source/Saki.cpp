#include "Saki.h"
#include "Controls.h"
#include "Fight.h"
#include <iostream>

using AdditionalEffect = DamageInfo::AdditionalEffect;

Saki::Saki() {
}

Saki::~Saki() {
}

void Saki::Load() {
	name = SAKI;
	//std::string name = SAKI;
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

	// SUPPORT ENTER
	temp = new Animation(charPath, SUPPORT_ENTER, 1, true);
	temp->AddBoundBox(0, sf::IntRect(20, 92, 50, 1));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(24, 15, 50, 71));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(SUPPORT_ENTER, temp);

	// SUPPORT
	temp = new Animation(charPath, SUPPORT, 10, false, SUPPORT_END);
	temp->AddFrameFunction(0, stop_x_movement);
	temp->AddFrameFunction(4, spawn_saki_beam);
	temp->AddBoundBox(0, sf::IntRect(20, 92, 50, 1));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(12, 26, 71, 68));
	temp->AddHurtBoxes(0, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(12, 15, 71, 79));
	temp->AddHurtBoxes(3, hurtBoxes);
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(15, 9, 71, 86));
	temp->AddHurtBoxes(4, hurtBoxes);
	animManager.AddAnimation(SUPPORT, temp);

	// SUPPORT END
	temp = new Animation(charPath, SUPPORT_END, 3, false, SUPPORT_EXIT);
	temp->AddBoundBox(0, sf::IntRect(20, 92, 50, 1));
	hurtBoxes.clear();
	hurtBoxes.push_back(sf::IntRect(58, 7, 50, 87));
	temp->AddHurtBoxes(0, hurtBoxes);
	animManager.AddAnimation(SUPPORT_END, temp);

	// SUPPORT EXIT
	temp = new Animation(charPath, SUPPORT_ENTER, 1, true);
	temp->AddBoundBox(0, sf::IntRect(20, 92, 50, 1));
	temp->AddFrameFunction(0, do_support_exit);
	temp->AddFrameFunction(0, destroy_saki_beam);
	animManager.AddAnimation(SUPPORT_EXIT, temp);

	//animManager.Play(IDLE, position, xScale);

	sakiBeamBase = new SakiBeam;
	sakiBeamBase->Load();

	Fighter::Load();
}

void Saki::UpdateAnimations() {
	Fighter::UpdateAnimations();
}

bool Saki::CallEnumFunction(int functionEnum) {

	if (Fighter::CallEnumFunction(functionEnum))
		return false;

	switch (functionEnum) {
	case spawn_saki_beam:
		SpawnSakiBeam();
		return true;
	case destroy_saki_beam:
		DestroySakiBeam();
		return true;
	default:
		std::cout << "Function: " << functionEnum << " not found" << std::endl;
		return false;
	}
}

void Saki::SpawnSakiBeam() {
	SakiBeam* newSakiBeam = new SakiBeam(*sakiBeamBase);
	newSakiBeam->SetXScale(xScale);
	newSakiBeam->SetPosition(position);

	spawnedProjectiles.push_back(newSakiBeam);
}

void Saki::DestroySakiBeam() {
	spawnedProjectiles.clear();
}

void Saki::SetColor(int colorNum) {
	if (2 == colorNum) {
		colorShader.setParameter("texture", sf::Shader::CurrentTexture);
		colorShader.setParameter("color1", 0.941f, 0.f, 0.f);
		colorShader.setParameter("replace1", 0.752f, 0.878f, 0.941f);
		colorShader.setParameter("color2", 0.690f, 0.f, 0.f);
		colorShader.setParameter("replace2", 0.501f, 0.564f, 0.815f);
		colorShader.setParameter("color3", 0.439f, 0.f, 0.f);
		colorShader.setParameter("replace3", 0.250f, 0.313f, 0.501f);
		colorShader.setParameter("color4", 0.376f, 0.439f, 0.501f);
		colorShader.setParameter("replace4", 0.501f, 0.439f, 0.439f);
		colorShader.setParameter("color5", 0.752f, 0.752f, 0.815f);
		colorShader.setParameter("replace5", 0.815f, 0.752f, 0.752f);
		colorShader.setParameter("color6", 0.250f, 0.250f, 0.313f);
		colorShader.setParameter("replace6", 0.313f, 0.250f, 0.250f);

		//colorShader.setParameter("color7", 0.223f, 0.223f, 0.321f);
		//colorShader.setParameter("replace7", 0.580f, 0.192f, 0.450f);
	}
}