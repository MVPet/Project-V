#include "Training.h"
#include "Fight.h"

#include <iostream>

Training::Training() {
}

Training::~Training() {
	delete fight;
}

void Training::Start() {
	fight = new Fight();
	fight->SetUpTrainingMatch();
}

void Training::UpdateEvent(sf::Event event) {
	fight->UpdateEvent(event);
}

void Training::Update() {
	fight->Update();
}

void Training::Draw(sf::RenderWindow* window) {
	fight->Draw(window);
}