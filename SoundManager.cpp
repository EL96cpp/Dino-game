#include "SoundManager.hpp"
#include "Global.hpp"
#include <SFML/Audio.hpp>

SoundManager& SoundManager::instance () {
    static SoundManager sm;
    return sm;
}

void SoundManager::Init() {
    jumpBuffer.loadFromFile(JUMP_SOUND_FILEPATH);
    pointBuffer.loadFromFile(POINT_SOUND_FILEPATH);
    dieBuffer.loadFromFile(DIE_SOUND_FILEPATH);

    sf::Sound jump(jumpBuffer);
    sf::Sound point(pointBuffer);
    sf::Sound die(dieBuffer);

    sounds["Jump"] = std::move(jump);
    sounds["Point"] = std::move(point);
    sounds["Die"] = std::move(die);

}

void SoundManager::Play(const std::string& sound_name) {
    sounds[sound_name].play();
}

