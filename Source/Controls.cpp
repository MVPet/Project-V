#include "Controls.h"

#include <stdio.h>
#include <iostream>

Controls::Controls(std::pair<Controls::ControlType, int> controls) {
	controlType = controls.first;
	controllerNumber = controls.second;

	// Default Controller Bindings
	if (ControlType::Keyboard == controlType) {
		switch (controllerNumber) {
		case 0:
			AddKeyBinding(Actions::KeyMoveLeft, sf::Keyboard::A);
			AddKeyBinding(Actions::KeyMoveRight, sf::Keyboard::D);
			AddKeyBinding(Actions::KeyMoveUp, sf::Keyboard::W);
			AddKeyBinding(Actions::KeyMoveDown, sf::Keyboard::S);
			AddKeyBinding(Actions::Light, sf::Keyboard::J);
			AddKeyBinding(Actions::Medium, sf::Keyboard::K);
			AddKeyBinding(Actions::Heavy, sf::Keyboard::L);
			AddKeyBinding(Actions::Special, sf::Keyboard::SemiColon);
			AddKeyBinding(Actions::Support, sf::Keyboard::I);
			AddKeyBinding(Actions::Jump, sf::Keyboard::W);
			AddKeyBinding(Actions::Pause, sf::Keyboard::Escape);
			break;
		case 1:
			AddKeyBinding(Actions::KeyMoveLeft, sf::Keyboard::Left);
			AddKeyBinding(Actions::KeyMoveRight, sf::Keyboard::Right);
			AddKeyBinding(Actions::KeyMoveUp, sf::Keyboard::Up);
			AddKeyBinding(Actions::KeyMoveDown, sf::Keyboard::Down);
			AddKeyBinding(Actions::Light, sf::Keyboard::Numpad4);
			AddKeyBinding(Actions::Medium, sf::Keyboard::Numpad5);
			AddKeyBinding(Actions::Heavy, sf::Keyboard::Numpad6);
			AddKeyBinding(Actions::Special, sf::Keyboard::Add);
			AddKeyBinding(Actions::Support, sf::Keyboard::Numpad8);
			AddKeyBinding(Actions::Jump, sf::Keyboard::Up);
			AddKeyBinding(Actions::Pause, sf::Keyboard::Return);
			break;
		default:
			printf("No default key binding for player:%d", controllerNumber);
		}
	}
	// Default Controller Bindings
	else if (ControlType::Controller == controlType) {
		AddButtonBinding(Actions::Light, 0);
		AddButtonBinding(Actions::Medium, 3);
		AddButtonBinding(Actions::Heavy, 2);
		AddButtonBinding(Actions::Special, 1);
		AddButtonBinding(Actions::Support, 5);
		AddButtonBinding(Actions::Pause, 9);
	}
}

Controls::~Controls() {

}

void Controls::SetControlType(Controls::ControlType type) {
	controlType = type;
}

void Controls::SetControllerNumber(int value) {
	controllerNumber = value;
}

void Controls::SetButtonBinding(Controls::Actions action, int buttton) {
	controllerMapping.find(action)->second = buttton;
}

void Controls::SetKeyBinding(Controls::Actions action, sf::Keyboard::Key key) {
	keyboardMapping.find(action)->second = key;
}

bool Controls::isActionPressed(Controls::Actions action, sf::Event event) {
	// Need to add in checks to see if second exists (i.e. if it is null)
	if (ControlType::Keyboard == controlType) {
		if (event.key.code == keyboardMapping.find(action)->second)
			return true;
		else
			return false;
	}
	else {
		if (controllerMapping.find(action) != controllerMapping.end())
			return (sf::Joystick::isButtonPressed(controllerNumber, controllerMapping.find(action)->second));
		else
			return false;
	}
}

bool Controls::isActionPressed(Controls::Actions action) {
	// Need to add in checks to see if second exists (i.e. if it is null)
	if (ControlType::Keyboard == controlType)
		return sf::Keyboard::isKeyPressed(keyboardMapping.find(action)->second);
	else
		if (controllerMapping.find(action) != controllerMapping.end())
			return (sf::Joystick::isButtonPressed(controllerNumber, controllerMapping.find(action)->second));
		else
			return false;
}

int Controls::GetHorizontalAxis() {
	sf::Joystick::update(); // Joystick is typically updated when an Event is captured, we call this to manually update it.

	float controllerXAxis;
	float dpadXAxis;

	switch (controlType) {
	case ControlType::Keyboard:
		if (sf::Keyboard::isKeyPressed(keyboardMapping.find(KeyMoveLeft)->second))
			return -1;
		else if (sf::Keyboard::isKeyPressed(keyboardMapping.find(KeyMoveRight)->second))
			return 1;
		else
			return 0;
		break;
	case ControlType::Controller:
		controllerXAxis = sf::Joystick::getAxisPosition(controllerNumber, sf::Joystick::X);
		dpadXAxis = sf::Joystick::getAxisPosition(controllerNumber, sf::Joystick::PovX);

		if (50 < dpadXAxis)
			return 1;
		else if (-50 > dpadXAxis)
			return -1;
		else if (50 < controllerXAxis)
			return 1;
		else if (-50 > controllerXAxis)
			return -1;
		else
			return 0;
		break;
	default:
		printf("\nUNSUPPORTED CONTROL TYPE\n");
		return 0;
		break;
	}
}

int Controls::GetVerticalAxis() {
	sf::Joystick::update(); // Joystick is typically updated when an Event is captured, we call this to manually update it.

	float controllerYAxis;
	float dpadYAxis;

	switch (controlType) {
	case ControlType::Keyboard:
		if (sf::Keyboard::isKeyPressed(keyboardMapping.find(KeyMoveUp)->second))
			return -1;
		else if (sf::Keyboard::isKeyPressed(keyboardMapping.find(KeyMoveDown)->second))
			return 1;
		else
			return 0;
	case ControlType::Controller:
		controllerYAxis = sf::Joystick::getAxisPosition(controllerNumber, sf::Joystick::Y);
		dpadYAxis = sf::Joystick::getAxisPosition(controllerNumber, sf::Joystick::PovY);

		if (50 < dpadYAxis)
			return -1;
		else if (-50 > dpadYAxis)
			return 1;
		else if (50 < controllerYAxis)
			return 1;
		else if (-50 > controllerYAxis)
			return -1;
		else
			return 0;
		break;
	default:
		printf("\nUNSUPPORTED CONTROL TYPE\n");
		return 0;
		break;
	}
}

void Controls::AddKeyBinding(Actions action, sf::Keyboard::Key key) {
	keyboardMapping.insert(std::make_pair(action, key));
}

void Controls::AddButtonBinding(Actions action, int button) {
	controllerMapping.insert(std::make_pair(action, button));
}