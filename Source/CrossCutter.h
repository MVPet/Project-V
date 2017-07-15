#pragma once

#include "Projectile.h"

class CrossCutter : public Projectile {
public:
	CrossCutter();
	~CrossCutter();

	void Load();
	void Update();
	bool CallEnumFunction(int functionEnum);

	void SetYScale(float newYScale);

private:
	enum EnumFunctions
	{
		cross_cutter_1 = Projectile::EnumFunctions::last, cross_cutter_2, cross_cutter_3,
	};

	void CrossCutter1();
	void CrossCutter2();
	void CrossCutter3();

	float yScale = 1;
};

static const string CROSS_CUTTER = "Cross_Cutter";