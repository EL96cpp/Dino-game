#include "State.hpp"
#include <SFML/Graphics.hpp>

State::State(sf::RenderWindow& w, std::stack<State*>* states) : window(w), quit(false), states(states) {}

bool State::getQuit() const {
    return quit;
}


void State::UpdateMousePosition() {
    mousePos = sf::Mouse::getPosition();
}
