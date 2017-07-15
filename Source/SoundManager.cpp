#include "SoundManager.h"
#include <cstdlib>

SoundManager::SoundManager() {

}

SoundManager::~SoundManager() {

}

void SoundManager::PlayMusic(std::string musicName) {
	std::string filePath = "Music/" + musicName + ".wav";

	if (!bgMusic.openFromFile(filePath)) {
		printf("CANNOT LOAD MUSIC: %s\n", filePath);
		return;
	}

	bgMusic.play();
	bgMusic.setLoop(true);
}

void SoundManager::StopMusic() {
	bgMusic.stop();
}

void SoundManager::PlaySFX(sf::SoundBuffer& soundBuf) {
	sfx.stop();
	sfx.setBuffer(soundBuf);
	sfx.play();
}