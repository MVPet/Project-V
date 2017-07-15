#pragma once

#include "Projectile.h"

class SakiBeam : public Projectile {
public:
	SakiBeam();
	~SakiBeam();

	void Load();
};

static const string SAKI_BEAM = "Saki_Beam";