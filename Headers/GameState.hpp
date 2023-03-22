#pragma once

#include <deque>
#include <memory>

#include <SFML/Graphics.hpp>
#include "Global.hpp"
#include "State.hpp"
#include "Obsticle.hpp"
#include "Player.hpp"

class GameState : public State {
    public:
        GameState(sf::RenderWindow& w, std::stack<State*>* states);

        void Init();
   
        void Scale();

        void HandleInput();
        
        void Update(const float& dt);

        void UpdateObsticles();

        void UpdateGameSpeed();

        void Render();

        void UpdateInput(const float& dt);

        void Restart();

    private:

        sf::Event event;

        bool game_over;
        bool pause_game;
        bool restart_game;
    
        std::deque<std::shared_ptr<Obsticle>> obsticles;
        Player player;

        sf::Sprite _ground;
        sf::Sprite _cloud1;
        sf::Sprite _cloud2;
        sf::Sprite _cloud3;
        sf::Sprite _cloud4;
        sf::Sprite _restart_button;
        sf::Text score_text;
        sf::Text max_score_text;
        sf::Text pause_text;
        sf::Text game_over_text;
        sf::RectangleShape pauseRect;

        int ground_move;
        float game_speed;
        float cloud_speed = 80;
        float score;
        float score_difference = 0;
        int max_score;
};
