#include "CommandList.h"

#include <iostream>

CommandList::CommandList() {
}

CommandList::~CommandList() {
}

void CommandList::AddCommand(std::string input, std::string animationName, int meterUsage) {
	commandList.insert(std::make_pair(input, animationName));
	AddMeterUsage(animationName, meterUsage);
}

bool CommandList::DoesCommandExist(std::string inputBuffer, int playerMeter) {

	std::string inputCheck = "";
	bool commandFound = false;
	for (int i = inputBuffer.length() - 1; i >= 0; i--) {
		inputCheck = inputBuffer[i] + inputCheck;
		if (1 == commandList.count(inputCheck)) {
			if (playerMeter >= meterUsageList[GetCommandAnimation(inputCheck)]) {
				foundCommand = GetCommandAnimation(inputCheck);
				commandFound = true;
			}
		}
	}

	return commandFound;
}

std::string CommandList::GetCommandAnimation(std::string input) {
	if (1 == commandList.count(input)) {
		return commandList.at(input);
	}
	else
		return "";
}

std::string CommandList::GetFoundCommand() {
	return foundCommand;
}

void CommandList::AddMeterUsage(std::string animName, int meterUsage) {
	if (0 == meterUsageList.count(animName)) {
		meterUsageList.insert(std::make_pair(animName, meterUsage));
	}
}

int CommandList::GetFoundCommandMeterUsage() {
	return ("" != foundCommand) ? meterUsageList[foundCommand] : 0;
}