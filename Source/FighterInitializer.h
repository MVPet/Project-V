#pragma once

#include <string>
#include <iostream>

#include "FighterStrings.h"
#include "Ryu.h"
#include "Kyosuke.h"
#include "Saki.h"
#include "TonPooh.h"

static Fighter* InitializeFighter(std::string name) {
	if (RYU == name) {
		Ryu* ryu = new Ryu();
		return ryu;
	}

	if (KYOSUKE == name) {
		Kyosuke* kyosuke = new Kyosuke();
		return kyosuke;
	}

	if (SAKI == name) {
		Saki* saki = new Saki();
		return saki;
	}

	if (TON_POOH == name) {
		TonPooh* tp = new TonPooh();
		return tp;
	}

}