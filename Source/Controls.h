#pragma once

#include <utility>
#include <map>
#include <SFML\Graphics.hpp>

class Controls {
public:
	enum ControlType { Keyboard, Controller };
	enum Actions { KeyMoveLeft, KeyMoveRight, KeyMoveUp, KeyMoveDown, Jump, Light, Medium, Heavy, Special, Support, Pause };

	Controls(std::pair<Controls::ControlType, int> controls);
	~Controls();

	void SetControlType(ControlType type);
	void SetControllerNumber(int value);

	void SetKeyBinding(Actions action, sf::Keyboard::Key key);
	void SetButtonBinding(Actions action, int button);

	bool isActionPressed(Actions action, sf::Event event);
	bool isActionPressed(Actions action);
	/*
	int GetKeyboardXAxis();
	int GetKeyboardYAxis();
	*/

	int GetHorizontalAxis();
	int GetVerticalAxis();

	//void SetKeyboardDefaults(int playerNumber); // Need playerNumber because p1 and p2 controls are different
	//void SetControllerDefaults(); // Joystick defaults are the same no matter what

private:
	void AddKeyBinding(Actions action, sf::Keyboard::Key key);
	void AddButtonBinding(Actions action, int button);

	ControlType controlType;
	int controllerNumber;
	std::map<Actions, sf::Keyboard::Key> keyboardMapping;
	std::map<Actions, int> controllerMapping;
};