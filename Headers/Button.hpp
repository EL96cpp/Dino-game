#pragma once 

#include "Global.hpp"
#include <SFML/Graphics.hpp>

enum ButtonStates {
    IDLE = 0,
    HOVER,
    PRESSED
};

class Button {
    public:
        Button(float x, float y, float width, float height, std::string text,
               sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor);

        const bool isPressed() const;

        void Update(sf::RenderWindow&, sf::Vector2i&);

        void Render(sf::RenderWindow&);

//    private:
        sf::RectangleShape shape;
        sf::Font* font;
        sf::Text text;
        ButtonStates button_state;

        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color pressedColor;
};
