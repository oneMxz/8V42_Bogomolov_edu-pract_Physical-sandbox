#ifndef MUSIC_H
#define MUSIC_H

#include <SFML/Audio.hpp>
#include <string>

class MusicManager {
public:
    MusicManager();
    
    bool load(const std::string& filename);
    void play();
    void pause();
    void stop();
    void setVolume(float volume);
    float getVolume() const;
    void toggle();
    bool isPlaying() const;

private:
    sf::Music music;
    float volume = 50.0f;
    bool playing = false;
};

#endif