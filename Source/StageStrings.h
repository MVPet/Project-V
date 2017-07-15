#pragma once

#include <string>

using namespace std;

const int NUM_OF_STAGES = 2;

// Stage strings
static const string SAGAT_ALPHA_2 = "Sagat_Alpha_2";
static const string SAKURA_ALPHA_2 = "Sakura_Alpha_2";
static const string RYU_ALPHA = "Ryu_Alpha";

static string* GetAllStageStrings() {
	string* stringList = new string[NUM_OF_STAGES];

	stringList[0] = SAGAT_ALPHA_2;
	stringList[1] = RYU_ALPHA;
	//stringList[1] = SAKURA_ALPHA_2;

	return stringList;
}