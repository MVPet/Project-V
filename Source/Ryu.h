#pragma once

#include <iostream>
#include "Fighter.h"
#include "Hadouken.h"
#include "Metsu_Haduken.h"

class Ryu : public Fighter {
public:
	Ryu();
	~Ryu();

	void SetColor(int colorNum);
	void Load();
	void LoadTatsumaki(std::string filePath);

	bool CallEnumFunction(int functionEnum);

protected:
	void UpdateAnimations();
	void CheckActionInput(Controls* playerControls);
	void CheckOnHit();
	void DoForwardThrow();
	void DoBackThrow();

private:
	// Try inheriting/overloading this enum
	enum EnumFunctions
	{
		spawn_hadouken = Fighter::FrameFunctions::last, spawn_metsu_hadouken, do_tatsumaki, do_shoryuken, do_shin_shoryuken, destroy_metsu_hadouken, do_m, do_c_m, do_h,
	};

	void SpawnHadouken();
	void SpawnMetsuHadouken();
	void DoTatsumaki();
	void DoShoryuken();
	void DoShinShoryuken();
	void DestroyMetsuHadouken();
	void DoM();
	void DoC_M();
	void DoH();

	Hadouken*		hadoukenBase;
	MetsuHadouken*	metsuHadoukenBase;
};

// Ryu Specific Strings
static const string COLLARBONE_BREAKER = "Collarbone_Breaker";
static const string ROUNDHOUSE_KICK = "Roundhouse_Kick";
static const string SHORYUKEN = "Shoryuken";
static const string L_TATSUMAKI = "L_Tatsumaki";
static const string M_TATSUMAKI = "M_Tatsumaki";
static const string H_TATSUMAKI = "H_Tatsumaki";
static const string SHIN_SHORYU1 = "Shin_Shoryu1";
static const string SHIN_SHORYU2 = "Shin_Shoryu2";
static const string SHIN_SHORYU3 = "Shin_Shoryu3";
static const string SHINKU_TATSUMAKI = "Shinku_Tatsumaki";
static const string SHINKU_ATSUMAKI_MIDDLE = "Shinku_Tatsumaki_Middle";
static const string SHINKU_TATSUMAKI_END = "Shinku_Tatsumaki_End";