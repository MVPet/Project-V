#pragma once

#include "Projectile.h"

class ShadowWave : public Projectile {
public:
	ShadowWave();
	~ShadowWave();

	void Load();
};

static const string SHADOW_WAVE = "Shadow_Wave";