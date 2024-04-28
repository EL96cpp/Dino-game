#include "Player.hpp"
#include "TextureManager.hpp"
#include "Global.hpp"
#include <math.h>
#include <SFML/Graphics.hpp>

Player::Player(sf::RenderWindow& window) : window(window), player_state(RUNNING), timer(1.f), y(PLAYER_Y) {}

void Player::Init() {
    TextureManager::instance().LoadTexture("Player", PLAYER_FILEPATH);
    _player.setTexture(TextureManager::instance().GetTexture("Player"));
    _player.setTextureRect(sf::IntRect(90, 0, 90, 95));
    _player.setPosition(PLAYER_X, PLAYER_Y);
}

void Player::Scale() {
    _player.scale(1.5, 1.5);
}


void Player::Update(const float& dt, const float& game_speed) {
    
    switch (player_state) {

        case RUNNING:
            timer += game_speed*dt;
            if (timer >= 3) timer = 1.f;
            _player.setTextureRect(sf::IntRect(90*int(timer), 0, 90, 95));
            _player.setPosition(PLAYER_X, PLAYER_Y);
            break;

        case DOWN:
            timer += game_speed*dt;
            if (timer >=3) timer = 1.f;
            _player.setTextureRect(sf::IntRect(90*int(timer + 3), 35, 90, 60));
            _player.setPosition(PLAYER_DX, PLAYER_DY);
            break;

        case JUMPING:
            _player.setTextureRect(sf::IntRect(0, 0, 90, 95));

            y += velocity_y * game_speed / 22;
            velocity_y += gravity_y * game_speed / 22;

            _player.setPosition(PLAYER_X, y);
            if (_player.getPosition().y >= PLAYER_Y) {
                player_state = RUNNING;
                y = PLAYER_Y;
                velocity_y = 0;
            }
            break;

        case DEAD:
            _player.setTextureRect(sf::IntRect(270, 0, 90, 95));
            break;
    }
}

void Player::Render(sf::RenderWindow& window) {
    window.draw(_player);
}

void Player::CheckColisions(std::deque<std::shared_ptr<Obsticle>>& obsticles) {
    sf::FloatRect player_rect(_player.getPosition().x, _player.getPosition().y, 
                                     _player.getGlobalBounds().width*0.70, _player.getGlobalBounds().height*0.70);
    for (auto& obs : obsticles) {
        sf::FloatRect obsticle_rect(obs->_obsticle.getPosition().x,
                                           obs->_obsticle.getPosition().y,
                                           obs->_obsticle.getGlobalBounds().width*0.70,
                                           obs->_obsticle.getGlobalBounds().height*0.70);
        if (player_rect.intersects(obsticle_rect)) {
            player_state = DEAD;
            break;
        }
    }
}
