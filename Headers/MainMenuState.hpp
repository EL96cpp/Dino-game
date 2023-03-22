#pragma once 

#include <memory>
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Button.hpp"

class MainMenuState : public State {
    public:
        MainMenuState(sf::RenderWindow& w, std::stack<State*>* states);
        
        void Init();

        void Update(const float& dt);
        void UpdateInput(const float& dt);
        void UpdateKeybinds(const float& dt);
        void UpdateButtons();
        void Render();

    private:
        sf::Clock _clock;
        std::shared_ptr<Button> Play;
        std::shared_ptr<Button> Options;
        std::shared_ptr<Button> Exit;
        sf::Event event;

        sf::Text game_title;
        sf::Sprite _background;
        sf::Sprite _cactus1;
        sf::Sprite _cactus2;
        sf::Sprite _cactus3;
        sf::Sprite _cactus4;
        sf::Sprite _cloud1;
        sf::Sprite _cloud2;
        sf::Sprite _tumble;
        
        const float cloud_speed = 80;
        const float tumble_speed = 500;
        const float tumble_rotation_speed = 500;
}; 

