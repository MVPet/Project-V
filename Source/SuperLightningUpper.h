#pragma once

#include "Projectile.h"

class SuperLightningUpper : public Projectile {
public:
	SuperLightningUpper();
	~SuperLightningUpper();

	void Load();
};

static const string SUPER_LIGHTNING_UPPER = "Super_Lightning_Upper";