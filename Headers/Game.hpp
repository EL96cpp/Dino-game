#pragma once 

#include <memory>
#include <string>
#include <stack>


#include <SFML/Graphics.hpp>
#include "Global.hpp"
#include "State.hpp"

#include "TextureManager.hpp"

class Game {
    public:
        Game();
    
        ~Game();

        void InitWindow();
    
        void InitStates();

        void Update();
        
        void Render();

        void Run();

        void UpdateEvents();

        void UpdateDt();

    private: 
        sf::RenderWindow window;
        sf::Clock dtClock;
        float dt;
        std::stack<State*> states;
};
