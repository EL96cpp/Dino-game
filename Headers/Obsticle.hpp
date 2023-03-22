#pragma once 

#include <SFML/Graphics.hpp>


class Obsticle {
    public:

        Obsticle(const int& start_x);

        virtual void Init() = 0;

        virtual void Update(const float& dt, const float& game_speed) = 0;

        virtual void Render(sf::RenderWindow&) = 0;

        int start_x;
        sf::Sprite _obsticle;
        
};
