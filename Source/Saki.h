#pragma once

#include "Fighter.h"
#include "SakiBeam.h"

class Saki : public Fighter {
public:
	Saki();
	~Saki();
	void Load();
	void SetColor(int colorNum);

	bool CallEnumFunction(int functionEnum);

protected:
	void UpdateAnimations();

private:
	enum EnumFunctions
	{
		spawn_saki_beam = Fighter::FrameFunctions::last, destroy_saki_beam,
	};

	void SpawnSakiBeam();
	void DestroySakiBeam();

	SakiBeam* sakiBeamBase;
};