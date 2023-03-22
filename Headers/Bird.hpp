#pragma once 

#include "Obsticle.hpp"
#include "TextureManager.hpp"

#include <SFML/Graphics.hpp>

class Bird : public Obsticle {
    public:
        Bird(const bool& is_upper, const int& start_x);

        void Init();

        void Update(const float& dt, const float& game_speed);

        void Render(sf::RenderWindow& w);

    private:
        float timer;
        int start_y;
        bool is_upper;
            
};
