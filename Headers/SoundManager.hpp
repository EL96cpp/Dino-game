#pragma once 

#include <map>
#include <string>

#include<SFML/Audio.hpp>

class SoundManager {
    public:
        static SoundManager& instance();

        void Init();
        
        void Play(const std::string& value);
        
    private:
        std::map<std::string, sf::Sound> sounds;        
        sf::SoundBuffer jumpBuffer;
        sf::SoundBuffer pointBuffer;
        sf::SoundBuffer dieBuffer;

};
