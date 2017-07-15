#pragma once

#include "Projectile.h"

class LightningUpper : public Projectile {
public:
	LightningUpper();
	~LightningUpper();

	void Load();
};

static const string LIGHTNING_UPPER = "Lightning_Upper";