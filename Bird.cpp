#include "Bird.hpp"
#include "Obsticle.hpp"
#include "Global.hpp"
#include "TextureManager.hpp"

#include <SFML/Graphics.hpp>

Bird::Bird(const bool& is_upper, const int& start_x) : is_upper(is_upper), Obsticle(start_x),
                                                       timer(0.0) {
    if (is_upper) {
        start_y = UPPER_BIRD_Y;
    } else {
        start_y = LOWER_BIRD_Y;
    }
    _obsticle.scale(1.5, 1.5);
    Init();
}

void Bird::Init() {
    TextureManager::instance().LoadTexture("Bird", BIRD_FILEPATH);
    _obsticle.setTexture(TextureManager::instance().GetTexture("Bird"));
    _obsticle.setTextureRect(sf::IntRect(0, 0, 90, 80));
    _obsticle.setPosition(start_x, start_y);
}

void Bird::Update(const float& dt, const float& game_speed) {
    _obsticle.move(-dt*game_speed*60, 0);
    timer += BIRD_SPEED*dt;
    if (timer >= 2.f) timer = 0.f;
    _obsticle.setTextureRect(sf::IntRect(90*int(timer), 0, 90, 80));
}

void Bird::Render(sf::RenderWindow& window) {
    window.draw(_obsticle);
}
