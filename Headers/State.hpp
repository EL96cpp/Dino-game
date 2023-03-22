#pragma once 

#include <SFML/Graphics.hpp>
#include <stack>

class State {
    protected:
        sf::RenderWindow& window;
        bool quit;
        sf::Vector2i mousePos;
        std::stack<State*>* states;

    public:
        State(sf::RenderWindow& window, std::stack<State*>* states);

        bool getQuit() const;

        virtual void Init() = 0;

        virtual void Update(const float&) = 0;
        virtual void Render() = 0;
        void UpdateMousePosition();
        virtual void UpdateInput(const float&) = 0;
};  
