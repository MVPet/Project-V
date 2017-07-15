#pragma once

#include "Projectile.h"

class Hadouken : public Projectile {
public:
	Hadouken();
	~Hadouken();

	void Load();
	void Update();

private:
};

static const string HADOUKEN = "Hadouken";