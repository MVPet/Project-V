#include "LocalVersus.h"
#include "Fight.h"

#include <iostream>

LocalVersus::LocalVersus() {
}

LocalVersus::~LocalVersus() {
	delete fight;
}

void LocalVersus::Start() {
	fight = new Fight();
}

void LocalVersus::UpdateEvent(sf::Event event) {
	fight->UpdateEvent(event);
	fight->SetUpLocalVersus();
}

void LocalVersus::Update() {
	fight->Update();
}

void LocalVersus::Draw(sf::RenderWindow* window) {
	fight->Draw(window);
}