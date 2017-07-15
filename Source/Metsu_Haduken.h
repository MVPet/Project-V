#pragma once

#include "Projectile.h"

class MetsuHadouken : public Projectile {
public:
	MetsuHadouken();
	~MetsuHadouken();

	void Load();
private:
};

static const string METSU_HADOUKEN = "Metsu_Hadouken";