#pragma once

#include "Fighter.h"
#include "LightningUpper.h"
#include "ShadowWave.h"
#include "SuperLightningUpper.h"
#include "CrossCutter.h"

class Kyosuke : public Fighter {
public:
	Kyosuke();
	~Kyosuke();

	void SetColor(int colorNum);
	void Load();
	
	bool CallEnumFunction(int functionEnum);

protected:
	void UpdateAnimations();
	void CheckActionInput(Controls* playerControls);
	void CheckOnHit();
	void DoForwardThrow();
	void DoBackThrow();

private:

	enum EnumFunctions
	{
		spawn_lightning_upper = Fighter::FrameFunctions::last, do_shadow_breaker, do_shadow_cut_kick, spawn_shadow_wave, spawn_super_lightning_upper, do_double_shadow_cut_kick_pt1, do_double_shadow_cut_kick_pt2, spawn_cross_cutter, spawn_super_cross_cutter,
		do_c_m, do_h,
	};

	void DoC_M();
	void DoH();
	void SpawnLightningUpper();
	void DoShadowBreaker();
	void DoShadowCutKick();
	void SpawnShadowWave();
	void SpawnSuperLightningUpper();
	void DoDoubleShadowCutKickPt1();
	void DoDoubleShadowCutKickPt2();
	void SpawnCrossCutter();
	void SpawnSuperCrossCutter();

	LightningUpper*			lightningUpperBase;
	ShadowWave*				shadowWaveBase;
	SuperLightningUpper*	superLightningUpperBase;
	CrossCutter*			crossCutterBase;
	CrossCutter*			crossCutterAltBase;
};

// Kyosuke Specific Strings
static const string SUPER_CROSS_CUTTER = "Super_Cross_Cutter";
static const string SHADOW_BREAKER = "Shadow_Breaker";
static const string SHADOW_CUT_KICK = "Shadow_Cut_Kick";
static const string DOUBLE_SHADOW_CUT_KICK = "Double_Shadow_Cut_Kick1";
static const string DOUBLE_SHADOW_CUT_KICK_2 = "Double_Shadow_Cut_Kick2";
static const string DOUBLE_SHADOW_CUT_KICK_3 = "Double_Shadow_Cut_Kick3";