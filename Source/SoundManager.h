#pragma once

#include <SFML\Audio.hpp>
#include <string>

class SoundManager {
public:
	SoundManager();
	~SoundManager();

	void PlayMusic(std::string musicName);
	void StopMusic();
	void PlaySFX(sf::SoundBuffer& soundBuf);

private:
	sf::Music bgMusic;
	sf::Sound sfx;
};