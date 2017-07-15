#pragma once

#include <SFML\Graphics.hpp>

struct DamageInfo {
public:	
	enum AdditionalEffect { None, Knockdown, Hard_KnockDown, Screen_Fly, OTG, Snap_Back };
	enum DamageScale { NoScale = 0, LightScale = 5, MediumScale = 4, HeavyScale = 3, SpecialScale = 2 };
	enum HitSparkType { Nothing, Light, Medium, Heavy, Guard };

	DamageInfo() {}

	DamageInfo(int d, int mGain, int hStun, int gStun, int hStop, char highOrLowAttack, sf::Vector2f kBack, DamageScale dScale = (DamageScale)(0), HitSparkType hSparkType = (HitSparkType)(0), bool ignoreInAirShift = false, AdditionalEffect addEffect = None, sf::Vector2f addKnockBack = sf::Vector2f(0,0)) {
		damage = d;
		meterGain = mGain;
		hitStun = hStun;
		blockStun = gStun;
		hitStop = hStop;
		highLowAttack = highOrLowAttack;
		knockback = kBack;
		damageScale = 1.f - (0.05f * (int)dScale);
		sparkType = hSparkType;
		ignoreAirShift = ignoreInAirShift;
		additionalEffect = addEffect;
		additionalEffectKnockback = addKnockBack;
	}

	int damage = 0;
	int meterGain = 0;
	int hitStun = 0;
	int blockStun = 0;
	int hitStop = 6;
	char highLowAttack = 1;
	bool ignoreAirShift = false;
	float damageScale;
	HitSparkType sparkType;
	sf::Vector2f knockback = sf::Vector2f(0, 0);
	AdditionalEffect additionalEffect = None;
	sf::Vector2f additionalEffectKnockback = sf::Vector2f(0, 0);
};