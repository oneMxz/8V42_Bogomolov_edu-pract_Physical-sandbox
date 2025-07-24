#include "music.h"
#include <iostream>
#include <SFML/Audio.hpp>

MusicManager::MusicManager() {
    // Конструктор
}

bool MusicManager::load(const std::string& filename) {
    if (!music.openFromFile(filename)) {
        std::cerr << "Failed to load music: " << filename << std::endl;
        return false;
    }
    
    music.setLoop(true);
    music.setVolume(volume);
    return true;
}

void MusicManager::play() {
    if (music.getStatus() != sf::Music::Playing) {
        music.play();
        playing = true;
    }
}

void MusicManager::pause() {
    if (music.getStatus() == sf::Music::Playing) {
        music.pause();
        playing = false;
    }
}

void MusicManager::stop() {
    if (music.getStatus() == sf::Music::Playing) {
        music.stop();
        playing = false;
    }
}

void MusicManager::setVolume(float volume) {
    this->volume = volume;
    if (volume > 100.0f) this->volume = 100.0f;
    if (volume < 0.0f) this->volume = 0.0f;
    
    music.setVolume(this->volume);
}

float MusicManager::getVolume() const {
    return volume;
}

void MusicManager::toggle() {
    if (isPlaying()) {
        pause();
    } else {
        play();
    }
}

bool MusicManager::isPlaying() const {
    return playing;
}
