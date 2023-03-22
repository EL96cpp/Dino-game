#include <fstream>

#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "Global.hpp"
#include "Obsticle.hpp"
#include "TextureManager.hpp"
#include "SoundManager.hpp"
#include "State.hpp"
#include "Cactus.hpp"
#include "Bird.hpp"
#include <time.h>

GameState::GameState(sf::RenderWindow& w, std::stack<State*>* states) : State(w, states), player(window),
                                                                        game_speed(8.f), ground_move(0), 
                                                                        game_over(false), pause_game(0), 
                                                                        restart_game(0), score(0) {
    
    std::ifstream readScore;
    readScore.open(SCORE_FILEPATH);
    if (readScore.is_open()) {
        while (!readScore.eof()) {
            readScore >> max_score;
        }
    }


    UpdateObsticles();
    Init();
    Scale(); 
}

void GameState::Init() {

    TextureManager::instance().LoadTexture("Ground", GROUND_FILEPATH);
    TextureManager::instance().LoadTexture("Button", RESTART_BUTTON_FILEPATH);

    score_text.setFont(TextureManager::instance().GetFont("Font"));
    score_text.setCharacterSize(50);
    score_text.setPosition(SCORE_X, SCORE_Y);
    score_text.setFillColor(sf::Color::Black);

    max_score_text.setFont(TextureManager::instance().GetFont("Font"));
    max_score_text.setCharacterSize(50);
    max_score_text.setPosition(SCORE_X, SCORE_Y + 60);
    max_score_text.setFillColor(sf::Color::Black);
   
    pause_text.setFont(TextureManager::instance().GetFont("Font"));
    pause_text.setCharacterSize(120);
    pause_text.setString("PAUSE");
    pause_text.setOrigin(pause_text.getLocalBounds().width/2, pause_text.getLocalBounds().height/2);
    pause_text.setFillColor(sf::Color::Black);
    pause_text.setPosition(SCREEN_WIDTH/2, 400);

    game_over_text.setFont(TextureManager::instance().GetFont("Font"));
    game_over_text.setCharacterSize(120);
    game_over_text.setString("GAME OVER");
    game_over_text.setOrigin(game_over_text.getLocalBounds().width/2, game_over_text.getLocalBounds().height/2);
    game_over_text.setFillColor(sf::Color::Black);
    game_over_text.setPosition(SCREEN_WIDTH/2, GAME_OVER_Y);

    _restart_button.setTexture(TextureManager::instance().GetTexture("Button"));
    _restart_button.setOrigin(_restart_button.getLocalBounds().width/2, 
                              _restart_button.getLocalBounds().height/2);
    _restart_button.setPosition(SCREEN_WIDTH/2, RESTART_BUTTON_Y);


    _ground.setTexture(TextureManager::instance().GetTexture("Ground"));
    _ground.setPosition(0, GROUND_Y);
    _cloud1.setTexture(TextureManager::instance().GetTexture("Cloud"));
    _cloud2.setTexture(TextureManager::instance().GetTexture("Cloud"));
    _cloud3.setTexture(TextureManager::instance().GetTexture("Cloud"));
    _cloud4.setTexture(TextureManager::instance().GetTexture("Cloud"));


    _cloud1.setPosition(CLOUD1_X, CLOUD1_Y);
    _cloud2.setPosition(CLOUD2_X, CLOUD2_Y);
    _cloud3.setPosition(CLOUD3_X, CLOUD3_Y);
    _cloud4.setPosition(CLOUD4_X, CLOUD4_Y);
    
    pauseRect.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    pauseRect.setFillColor(sf::Color(0, 0, 0, 75));
    pauseRect.setPosition(0, 0);

    player.Init();
    for (auto& obs : obsticles) {
        obs->Init();
    }

    SoundManager::instance().Init();
}

void GameState::Scale() {
    
    player.Scale();
    _restart_button.scale(2.5, 2.5);
    _cloud1.scale(3, 3);
    _cloud2.scale(3, 3);
    _cloud3.scale(3, 3);
    _cloud4.scale(3, 3);
    _ground.scale(1.5, 1.5);

}

void GameState::UpdateObsticles() {
    std::srand(std::time(NULL));
    static int obs_type, n, start_x;
    n = (score > 300) ? 5 : 3;
    while (obsticles.size() < 5) {
        obs_type = std::rand()%n;
        if (obsticles.empty()) {
            start_x = SCREEN_WIDTH;
        } else {
            start_x = obsticles.back()->_obsticle.getPosition().x + 
                      obsticles.back()->_obsticle.getLocalBounds().width + OBS_STEP + std::rand()%301;
        }
        switch (obs_type) {
            case 0:
                obsticles.push_back(std::make_shared<Cactus>(Cactus(obs_type, start_x)));
                break;
            case 1:
                obsticles.push_back(std::make_shared<Cactus>(Cactus(obs_type, start_x)));
                break;
            case 2:
                obsticles.push_back(std::make_shared<Cactus>(Cactus(obs_type, start_x)));
                break;
            case 3:
                obsticles.push_back(std::make_shared<Bird>(Bird(true, start_x)));
                break;
            case 4:
                obsticles.push_back(std::make_shared<Bird>(Bird(false, start_x)));
                break;
        }   
    }

    for (auto& obs : obsticles) {
        if (obs->_obsticle.getPosition().x < -400) {
            obsticles.pop_front();
        }
    }
}

void GameState::UpdateGameSpeed() {
    
    if (score >= 200 && score < 400) {
        game_speed = 10.f;
    } 

    if (score >= 400 && score < 600) {
        game_speed = 12.f;
    }

    if (score >= 600 && score < 800) {
        game_speed = 14.f;
    }

    if (score >= 800 && score < 1000) {
        game_speed = 16.f;
    }
}

void GameState::Update(const float& dt) {

    UpdateInput(dt);

    if (score < 1000) {
        UpdateGameSpeed();
    }

    if (pause_game == false && game_over == false) {
        UpdateObsticles();
        player.Update(dt, game_speed);
        ground_move += dt * game_speed * 60;
        score_difference += game_speed / 550;
        score += game_speed / 550;
        static std::string score_string;
        static std::string max_score_string;
        score_string = std::to_string(int(score));
        max_score_string = std::to_string(int(max_score));
        score_string.insert(0, 7 - score_string.length(), '0');
        max_score_string.insert(0, 7 - max_score_string.length(), '0');
        score_text.setString(score_string);
        max_score_text.setString(max_score_string);
        if (score_difference > 100) {
            SoundManager::instance().Play("Point");
            score_difference = 0.f;
        }
	    if (ground_move >= 1200) ground_move = 0;
        
        for (auto& obs : obsticles) {
            obs->Update(dt, game_speed);
        }

	    _ground.setTextureRect(sf::IntRect(0 + ground_move, 0, SCREEN_WIDTH, 20));
	    _cloud1.move(-cloud_speed * dt, 0.f);
	    _cloud2.move(-cloud_speed * dt, 0.f);
	    _cloud3.move(-cloud_speed * dt, 0.f);
	    _cloud4.move(-cloud_speed * dt, 0.f);
	    if (_cloud1.getPosition().x < -300) _cloud1.setPosition(CLOUD1_X, CLOUD1_Y);
	    if (_cloud2.getPosition().x < -300 - (CLOUD2_X - CLOUD1_X)) _cloud2.setPosition(CLOUD2_X, CLOUD2_Y);
	    if (_cloud3.getPosition().x < -300) _cloud3.setPosition(CLOUD3_X, CLOUD3_Y);
	    if (_cloud4.getPosition().x < -300 - (CLOUD4_X - CLOUD3_X)) _cloud4.setPosition(CLOUD4_X, CLOUD4_Y);
        player.CheckColisions(obsticles);
        if (player.player_state == DEAD) {
            SoundManager::instance().Play("Die");
            player.Update(dt, game_speed);
            game_over = true;
        }
    }
}

void GameState::Render() {

    window.clear(sf::Color(255, 255, 255));

    window.draw(_ground);
    window.draw(_cloud1);
    window.draw(_cloud2);
    window.draw(_cloud3);
    window.draw(_cloud4);
    window.draw(score_text);
    window.draw(max_score_text);
    player.Render(window);
    for (auto& obs : obsticles) {
        obs->Render(window);
    }
    if (pause_game == true) {
        window.draw(pauseRect);   
        window.draw(pause_text);
    } else if (game_over == true) {
        player.Render(window);
        window.draw(_restart_button);
        window.draw(game_over_text);
    }
}

void GameState::UpdateInput(const float& dt) {
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        if (pause_game == true) {
            pause_game == false;
        } else {
            quit = true;
        }
    }
    if (player.player_state != DEAD) {
	    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
	        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) &&
	            player.player_state != JUMPING) {
	        player.player_state = DOWN;
	    } else {
	        if (player.player_state != JUMPING) {
	            player.player_state = RUNNING;
	        }
	    }
	
	    while (window.pollEvent(event)) {
	        if (event.type == sf::Event::KeyPressed) {
	            if ((event.key.code == sf::Keyboard::Space ||
	                event.key.code == sf::Keyboard::W ||
	                event.key.code == sf::Keyboard::Up) &&
	                player.player_state != JUMPING ) {
	
	                player.velocity_y = -15;  
	                player.player_state = JUMPING;
                    SoundManager::instance().Play("Jump");
	            
	            }
	            if (event.key.code == sf::Keyboard::P) {
	                if (pause_game == true) {
	                    pause_game = false;
	                } else {
	                    pause_game = true;
	                }
	            }
	        }
	    }
    } else {
        while (window.pollEvent(event)) {
            State::UpdateMousePosition();
            sf::Vector2f vec(mousePos);
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left &&
                _restart_button.getGlobalBounds().contains(vec)) {
                Restart();
            }
        }
    }
}

void GameState::Restart() {

    if (score > max_score) {
        max_score = score;
        std::ofstream writeScore(SCORE_FILEPATH);
        if (writeScore.is_open()) {
            writeScore << max_score;
        }
        writeScore.close();
    }
    score = 0;
    score_difference = 0;
    game_speed = 8.f;
    obsticles.clear();
    window.clear();
    UpdateObsticles();
    Init();
    game_over = false;
    player.player_state = RUNNING;
}
