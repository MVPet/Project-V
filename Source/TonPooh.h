#pragma once

#include "Fighter.h"

class TonPooh : public Fighter {
public:
	TonPooh();
	~TonPooh();
	void Load();
	void SetColor(int colorNum);

	bool CallEnumFunction(int functionEnum);

protected:
	void UpdateAnimations();

private:
	enum EnumFunctions
	{
		do_support_attack = Fighter::FrameFunctions::last,
	};

	void DoSupportAttack();
};