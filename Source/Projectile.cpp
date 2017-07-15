#include "Projectile.h"
#include <iostream>

Projectile::Projectile() {
}

Projectile::~Projectile() {
}

void Projectile::Update() {
	lifeTime++;
	position.x += velocity.x;
	position.y += velocity.y;

	animManager.Update(position, xScale, this);
}

void Projectile::Draw(sf::RenderWindow* window) {
	animManager.Draw(window, sf::Color::White);
}

void Projectile::SetXScale(int scale) {
	xScale = scale;
}

void Projectile::SetPosition(sf::Vector2f newPosition) {
	position = sf::Vector2f(newPosition.x + (spawnOffset.x * xScale), newPosition.y + spawnOffset.y);
}

void Projectile::SetVelocity(sf::Vector2f newVelocity) {
	velocity = newVelocity;
}

bool Projectile::IsItTimeToDestroy() {
	if (lifeTime >= lifeLimit)
		return true;

	if ((animManager.GetCurrentAnimation()->GetName() == destroyOnAnim || animManager.GetCurrentAnimation()->GetName() == altDestroyOnAnim) && animManager.IsCurrentAnimationDone())
		return true;

	return false;
}

void Projectile::Load() {
}

bool Projectile::CallEnumFunction(int functionEnum) {
	switch (functionEnum) {
	case reset_has_hit:
		hasHitMain = false;
		hasHitSupport = false;
		return true;
	default:
		std::cout << "Projectile Function: " << functionEnum << " not found" << std::endl;
		return false;
	}

	return false;
}

void Projectile::CheckEnemyProjectileCollision(Fighter* enemy) {
	if (999 == durability)
		return;

	std::vector<Projectile*>* enemyProjectiles = enemy->GetSpawnedProjectiles();

	if (enemyProjectiles->empty())
		return;

	sf::IntRect ourHitBox = animManager.GetCurrentAnimation()->GetHitBox();
	sf::IntRect enemyHitBox;

	for (int i = 0; i < enemyProjectiles->size(); i++) {
		enemyHitBox = enemyProjectiles->at(i)->animManager.GetCurrentAnimation()->GetHitBox();
		if (ourHitBox.intersects(enemyHitBox)) {
			ReduceDurability(enemyProjectiles->at(i)->GetDurability());
		}
	}
}

bool Projectile::CheckEnemyCollision(Fighter* owner, Fighter* enemy) {
	CheckEnemyProjectileCollision(enemy);

	DamageInfo dInfo = animManager.GetCurrentAnimation()->GetDamageInfo();
	dInfo.knockback.x *= xScale;
	dInfo.additionalEffectKnockback.x *= xScale;

	sf::IntRect enemyHitBox = enemy->GetAnimationManager().GetCurrentAnimation()->GetHitBox();
	sf::IntRect ourHitBox = animManager.GetCurrentAnimation()->GetHitBox();

	if (((!enemy->GetIsSupport() && !hasHitMain) || (enemy->GetIsSupport() && !hasHitSupport)) && ourHitBox.intersects(enemyHitBox)) {
		sf::Vector2f pointOfCollision;
		pointOfCollision.x = (position.x < enemy->GetPosition().x) ? enemyHitBox.left : enemyHitBox.left + enemyHitBox.width;
		pointOfCollision.y = ((ourHitBox.top + ourHitBox.height * 0.5f) + (enemyHitBox.top + enemyHitBox.height * 0.5f)) * 0.5f;
		if (enemy->TakeDamage(dInfo, pointOfCollision, owner->GetCombo())) {
			owner->IncrementCombo();
		}
		owner->AddSpecialMeter(dInfo.meterGain);
		if(enemy->GetIsSupport())
			hasHitSupport = true;
		else
			hasHitMain = true;
		owner->SetCanCombo(true);
		return true;
	}

	std::vector<sf::IntRect> enemyHurtBoxes = enemy->GetAnimationManager().GetCurrentAnimation()->GetHurtBoxes();
	for (int i = 0; i < enemyHurtBoxes.size(); i++) {
		if (((!enemy->GetIsSupport() && !hasHitMain) || (enemy->GetIsSupport() && !hasHitSupport)) && ourHitBox.intersects(enemyHurtBoxes[i])) {
			sf::Vector2f pointOfCollision;
			pointOfCollision.x = (position.x < enemy->GetPosition().x) ? enemyHurtBoxes[i].left : enemyHurtBoxes[i].left + enemyHurtBoxes[i].width;
			pointOfCollision.y = ((ourHitBox.top + (ourHitBox.height * 0.5f)) + (enemyHurtBoxes[i].top + (enemyHurtBoxes[i].height * 0.5f))) * 0.5f;
			if (enemy->TakeDamage(dInfo, pointOfCollision, owner->GetCombo())) {
				owner->IncrementCombo();
			}
			owner->AddSpecialMeter(dInfo.meterGain);
			if (enemy->GetIsSupport())
				hasHitSupport = true;
			else
				hasHitMain = true;
			owner->SetCanCombo(true);
			return true;
		}
	}
}

std::string Projectile::GetName() {
	return name;
}

void Projectile::ReduceDurability(int damage) {
	durability -= damage;

	noDurability = (0 >= durability);
}

void Projectile::SetMaxDurability(int value) {
	maxDurability = value;
	durability = maxDurability;
}

int Projectile::GetDurability() {
	return maxDurability;
}
