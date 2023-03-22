#include "Cactus.hpp"
#include "TextureManager.hpp"

Cactus::Cactus(const int& type, const int& start_x) : type(type), Obsticle(start_x) {
    switch (type) {
        case 1:
            _obsticle.setTexture(TextureManager::instance().GetTexture("Cactus1"));
            _obsticle.scale(1.2, 1.2);
            start_y = CACTUS1_Y;
            break;
        
        case 2:
            _obsticle.setTexture(TextureManager::instance().GetTexture("Cactus2"));
            _obsticle.scale(1.5, 1.5);
            start_y = CACTUS2_Y;
            break;

        case 3:
            _obsticle.setTexture(TextureManager::instance().GetTexture("Cactus3"));
            start_y = CACTUS3_Y;
            _obsticle.scale(1.5, 1.5);
            break;
    }
    Init();
}

void Cactus::Init() {

    _obsticle.setPosition(start_x, start_y);

}

void Cactus::Update(const float& dt, const float& game_speed) {
    _obsticle.move(-game_speed*dt*60, 0);
}

void Cactus::Render(sf::RenderWindow& w) {
    w.draw(_obsticle);
}
