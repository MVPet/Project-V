#pragma once

#include <unordered_map>
#include <string>

class CommandList
{
public:
	CommandList();
	~CommandList();

	void AddCommand(std::string input, std::string animationName, int meterUsage = 0);
	bool DoesCommandExist(std::string inputBuffer, int playerMeter = 0);
	std::string GetFoundCommand();
	std::string GetCommandAnimation(std::string input);
	int GetFoundCommandMeterUsage();

private:
	void AddMeterUsage(std::string animName, int meterUsage);
	//void DoesMeterUsageExist();

	std::unordered_map<std::string, std::string> commandList;
	std::unordered_map<std::string, int> meterUsageList;

	std::string foundCommand = "";
};