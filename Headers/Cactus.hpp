#pragma once 

#include "Obsticle.hpp"
#include "Global.hpp"

class Cactus : public Obsticle {
    public:
        Cactus(const int& type, const int& start_x);
        
        void Update(const float& dt, const float& game_speed);

        void Render(sf::RenderWindow& window);

        void Init();
        
    private:
        int start_y;
        int type;
};
