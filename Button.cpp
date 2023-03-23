#include "Button.hpp"

Button::Button(float x, float y, float width, float height, 
               std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor) :
               shape(sf::Vector2f(width, height)), idleColor(idleColor),
               hoverColor(hoverColor), pressedColor(pressedColor) {
                    shape.setOrigin(width / 2, height / 2);
                    shape.setPosition(x, y);
                    shape.setFillColor(idleColor);
                    shape.setOutlineColor(sf::Color::Black);
                    shape.setOutlineThickness(5);
                    button_state = IDLE;
                    this->text.setCharacterSize(50);
                    this->text.setString(text);
                    this->text.setFillColor(sf::Color(0, 0, 0));
}
                
const bool Button::isPressed() const {
    if (button_state == PRESSED) {
        return true;
    }
    return false;
}

void Button::Update(sf::RenderWindow& window, sf::Vector2i& mousePos) {
    this->button_state = IDLE;
    sf::Vector2f vec(mousePos);

    if (this->shape.getGlobalBounds().contains(vec)){
      button_state = HOVER;
    }
    
    switch(button_state) {
        case IDLE:
            shape.setFillColor(idleColor);
            break;

        case HOVER:
            shape.setFillColor(hoverColor);
            break;

        case PRESSED:
            shape.setFillColor(pressedColor);
            break;
    }
}

void Button::Render(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}
