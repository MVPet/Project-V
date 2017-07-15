#include "Player.h"
#include "ApplicationData.h"
#include "FighterInitializer.h"
#include "Fighter.h"
#include "Controls.h"
#include "Fight.h"
#include <iostream>

//Player::Player(int playerNum, Fighter* fighter1, Fighter* fighter2) {
Player::Player(int playerNum, std::string fighter1, std::string fighter2) {
	main = InitializeFighter(fighter1);
	main->Load(); // Must be called here not in the constructor so the derived function can be used
	main->SetPlayer(this);

	support = InitializeFighter(fighter2);
	support->isSupport = true;
	support->Load();
	support->SetPlayer(this);
	support->disableGrav = true;
	if (!support->isPlayable) main->SetSoloFighter();

	playerNumber = playerNum;

	if (1 == playerNumber)
		playerControls = new Controls(ApplicationData::player1Controls);
	else if (2 == playerNumber)
		playerControls = new Controls(ApplicationData::player2Controls);
}

Player::~Player() {
	delete main;
	delete playerControls;
}

void Player::UpdateEvent(sf::Event event) {
	//main->UpdateEvent(event, playerControls);
}

void Player::CheckInput() {
	main->CheckInput(playerControls);
	// NOT CHECKING SUPPORT'S INPUT
}

void Player::CheckEnemyCollision(Fighter* enemy) {
	main->CheckEnemyCollision(enemy);
	support->CheckEnemyCollision(enemy);
}

void Player::CheckBoundaryCollision() {
	main->CheckBoundaryCollision();
	support->CheckBoundaryCollision();
}

void Player::Update(Fighter* enemy) {
	main->Update(enemy);
	support->Update(enemy);

	if (0 < timeUntilDeathSwap) {
		timeUntilDeathSwap--;
		if (0 == timeUntilDeathSwap)
			DeathSwap();
	}
}

/*
void Player::Draw(sf::RenderWindow* window) {
	if (support->GetKOed()) {
		support->Draw(window);
		main->Draw(window);
	}
	else {
		main->Draw(window);
		support->Draw(window);
	}
}
*/
void Player::DrawMain(sf::RenderWindow* window) {
	main->Draw(window);
}

void Player::DrawSupport(sf::RenderWindow* window) {
	support->Draw(window);
}

sf::Vector2f Player::GetPosition() {
	return main->GetPosition();
}

void Player::SetPosition(sf::Vector2f newPosition) {
	main->SetPosition(newPosition);

	if (2 == playerNumber) {
		support->SetPosition(sf::Vector2f(Fight::GetStage()->GetRightBound() + support->GetAnimationManager().GetAnimation(SUPPORT_IDLE)->GetOrigin().x, support->GetPosition().y));
	}
	else {
		support->SetPosition(sf::Vector2f(Fight::GetStage()->GetLeftBound() - support->GetAnimationManager().GetAnimation(SUPPORT_IDLE)->GetOrigin().x, support->GetPosition().y));
	}
}

Fighter* Player::GetMain() {
	return main;
}

Fighter* Player::GetSupport() {
	return support;
}

int Player::GetCurrentCombo() {
	return main->GetCombo() + support->GetCombo();
}

void Player::ResetCombo() {
	main->ResetCombo();
	support->ResetCombo();
}

int Player::GetPlayerNumber() {
	return playerNumber;
}

void Player::SummonSupport(sf::Vector2f mainPosition, int mainXScale) {
	support->SummonSupport(mainPosition, mainXScale);
}

void Player::SetMainEnemy(Fighter* mainEnemy) {
	main->SetMainEnemy(mainEnemy);
}

void Player::DoCrossAssault(sf::Vector2f mainPosition, int mainXScale) {
	if (!support->GetIsPlayable() && !support->GetKOed())
		return;

	Fight::cameraLock = true;
	support->isSupport = false;
	support->CrossAssault(mainPosition, mainXScale);
	main->isSupport = true;
	main->isAssisting = true;
	main->SetNextAnimToPlay(SUPPORT_END);
	Fighter* swap_temp = support;
	support = main;
	main = swap_temp;
	main->specialMeter = support->specialMeter;
	main->redMeter = main->healthMeter;
}

void Player::SnapBackSwap() {
	if (support->GetIsPlayable() && !support->GetKOed()) {
		Fighter* swap_temp = support;
		support = main;
		main = swap_temp;
		main->SetPosition(support->GetPosition());
		main->xScale = support->xScale;
		main->specialMeter = support->specialMeter;
		main->redMeter = main->healthMeter;
		support->isSupport = true;
		support->isAssisting = false;
		support->SetNextAnimToPlay(SUPPORT_EXIT);
		support->xScale *= -1;
	}

	Fight::cameraLock = false;
	sf::Vector2f position;
	if (1 == main->xScale) {
		position.x = (Fight::GetCamera().getCenter().x - Fight::GetCamera().getSize().x * 0.5f) - main->GetAnimationManager().GetCurrentAnimation()->GetOrigin().x;
	}
	else {
		position.x = (Fight::GetCamera().getCenter().x + Fight::GetCamera().getSize().x * 0.5f) + main->GetAnimationManager().GetCurrentAnimation()->GetOrigin().x;
	}

	position.y = (Fight::GetCamera().getCenter().y) - main->GetAnimationManager().GetCurrentAnimation()->GetOrigin().y;

	main->ResetToIdle();
	main->SetNextAnimToPlay(FALLING);
	main->inAir = true;
	main->isAssisting = false;
	main->isSupport = false;
	main->SetPosition(position);
	main->SetNewVelocityX(3.f * main->xScale);
	main->SetNewVelocityY(-7.f);
}

void Player::HyperSwap() {
	if (!canHyperSwap || support->GetKOed())
		return;

	if (1 == playerNumber)
		Fight::p1HyperSwap = true;
	else
		Fight::p2HyperSwap = true;

	Fight::cameraLock = true;
	support->isSupport = false;
	support->isAttacking = true;
	support->HyperSwap(main->GetPosition(), main->xScale);
	main->isSupport = true;
	main->isAssisting = true;
	main->inAir = false;
	main->SetNextAnimToPlay(SUPPORT_EXIT);
	Fighter* swap_temp = support;
	support = main;
	main = swap_temp;
	main->specialMeter = support->specialMeter;
	main->redMeter = main->healthMeter;
	canHyperSwap = false;
}

void Player::DeathSwap() {
	if (support->GetIsPlayable() && !support->GetKOed()) {
		Fighter* swap_temp = support;
		support = main;
		main = swap_temp;
		main->xScale = support->xScale;
		main->specialMeter = support->specialMeter;
		main->redMeter = main->healthMeter;
		support->isSupport = true;
		support->isAssisting = false;
	}
	else
		return;

	Fight::cameraLock = false;
	sf::Vector2f position;
	if (1 == main->xScale) {
		position.x = (Fight::GetCamera().getCenter().x - Fight::GetCamera().getSize().x * 0.5f);
	}
	else {
		position.x = (Fight::GetCamera().getCenter().x + Fight::GetCamera().getSize().x * 0.5f);
	}

	position.y = (Fight::GetCamera().getCenter().y) - main->GetAnimationManager().GetCurrentAnimation()->GetOrigin().y;

	main->isAssisting = false;
	main->isSupport = false;
	main->inAir = true;
	main->SetNextAnimToPlay(FALLING);
	main->SetPosition(position);
	main->SetNewVelocityX(3.f * main->xScale);
	main->SetNewVelocityY(-7.f);
	main->ResetToIdle();
}

Controls* Player::GetControls() {
	return playerControls;
}

void Player::SetReadyIntro(bool readyIntro) {
	main->SetReadyIntro(readyIntro);
	support->SetReadyIntro(readyIntro);
}

void Player::StartDeathSwap() {
	timeUntilDeathSwap = 30;
}

bool Player::CheckFightersHealth() {
	if (main->inAir)
		return false;

	return (main->GetKOed() && (!support->GetIsPlayable() || (support->GetIsPlayable() && support->GetKOed())));
}

void Player::FightIsOver(int winnerNumber) {
	main->FightIsOver(winnerNumber == playerNumber);
	support->FightIsOver(winnerNumber == playerNumber);
}

float Player::GetTotalRemainingHealth() {
	float remainHealth = main->GetPercentHealth();

	if (support->GetIsPlayable()) {
		remainHealth += support->GetPercentHealth();
		remainHealth *= 0.5f;
	}

	return remainHealth;
}

void Player::SetDrawOrder(bool onTopLayer) {
	drawFirst = onTopLayer;
}

bool Player::GetDrawFirst() {
	return drawFirst;
}

void Player::SetColors(int mainColor, int supportColor) {
	main->SetColor(mainColor);
	support->SetColor(supportColor);
}