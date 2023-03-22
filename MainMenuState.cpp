#include <sstream>
#include "MainMenuState.hpp"
#include "Global.hpp"
#include "TextureManager.hpp"
#include "State.hpp"
#include "GameState.hpp"
#include "OptionsState.hpp"

#include <iostream>
#include <memory>

MainMenuState::MainMenuState(sf::RenderWindow& w, std::stack<State*>* states) : State(w, states) {

    Play = std::make_shared<Button>(SCREEN_WIDTH/2, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, "PLAY", sf::Color(220,220,220), 
                                    sf::Color(153,153,153), sf::Color(102,102,102));

    Options = std::make_shared<Button>(SCREEN_WIDTH/2, BUTTON_Y + BUTTON_HEIGHT + BUTTON_STEP, BUTTON_WIDTH, BUTTON_HEIGHT, 
                                       "OPTIONS", sf::Color(220,220,220), sf::Color(153,153,153), sf::Color(102,102,102));

    Exit = std::make_shared<Button>(SCREEN_WIDTH/2, BUTTON_Y + (BUTTON_HEIGHT + BUTTON_STEP)*2 , BUTTON_WIDTH, BUTTON_HEIGHT, 
                                    "EXIT", sf::Color(220,220,220), sf::Color(153,153,153), sf::Color(102,102,102));
    Init();

}

void MainMenuState::Init() {

    TextureManager::instance().LoadTexture("Background", BACKGROUND_FILEPATH);
    TextureManager::instance().LoadTexture("Cloud", CLOUD_FILEPATH);
    TextureManager::instance().LoadTexture("Cactus1", CACTUS_FILEPATH_1);
    TextureManager::instance().LoadTexture("Cactus2", CACTUS_FILEPATH_2);
    TextureManager::instance().LoadTexture("Cactus3", CACTUS_FILEPATH_3);
    TextureManager::instance().LoadTexture("Tumble", TUMBLE_FILEPATH);
    TextureManager::instance().LoadFont("Font", FONT_FILEPATH);

    game_title.setString("DINO RUN");
    game_title.setCharacterSize(170);
    game_title.setStyle(sf::Text::Bold);
    game_title.setFont(TextureManager::instance().GetFont("Font"));
    game_title.setFillColor(sf::Color::Black);
    game_title.setOrigin(game_title.getLocalBounds().width / 2.f,
                         game_title.getLocalBounds().height / 2.f);

    Play->text.setFont(TextureManager::instance().GetFont("Font"));
    Options->text.setFont(TextureManager::instance().GetFont("Font"));
    Exit->text.setFont(TextureManager::instance().GetFont("Font"));

    game_title.setPosition(SCREEN_WIDTH / 2, 200);
    _background.setTexture(TextureManager::instance().GetTexture("Background"));
    _cactus1.setTexture(TextureManager::instance().GetTexture("Cactus2"));      
    _cactus2.setTexture(TextureManager::instance().GetTexture("Cactus3"));          
    _cactus3.setTexture(TextureManager::instance().GetTexture("Cactus3"));  
    _cactus4.setTexture(TextureManager::instance().GetTexture("Cactus3"));  
    _cloud1.setTexture(TextureManager::instance().GetTexture("Cloud"));
    _cloud2.setTexture(TextureManager::instance().GetTexture("Cloud"));
    _tumble.setTexture(TextureManager::instance().GetTexture("Tumble"));

    _cactus1.scale(1.2, 1.2);
    _cactus2.scale(3.8, 3.8);
    _cactus3.scale(1.3, 1.3);
    _cactus4.scale(3.2, 3.2);
    _cloud1.scale(3.4, 3.4);
    _cloud2.scale(3.7, 3.7);
    _tumble.scale(2, 2);


    _cactus1.setPosition(1400, 650);
    _cactus2.setPosition(300, 670);
    _cactus3.setPosition(550, 645);
    _cactus4.setPosition(1530, 725);
    _cloud1.setPosition(CLOUD1_MX, CLOUD1_MY);
    _cloud2.setPosition(CLOUD2_MX, CLOUD2_MY);
    _tumble.setPosition(TUMBLE_X, TUMBLE_Y);
    _tumble.setOrigin(25, 22);

    sf::FloatRect rec = Play->text.getLocalBounds();
    Play->text.setOrigin(rec.width / 2, rec.height / 2);
    Play->text.setPosition(Play->shape.getPosition().x, Play->shape.getPosition().y);

    rec = Options->text.getLocalBounds();
    Options->text.setOrigin(rec.width / 2, rec.height / 2);
    Options->text.setPosition(Options->shape.getPosition().x, Options->shape.getPosition().y);

    rec = Exit->text.getLocalBounds();
    Exit->text.setOrigin(rec.width / 2, rec.height / 2);
    Exit->text.setPosition(Exit->shape.getPosition().x, Exit->shape.getPosition().y);

}


void MainMenuState::Update(const float& dt) {
    State::UpdateMousePosition();
    UpdateInput(dt);
    UpdateButtons();
    UpdateKeybinds(dt);
    if (getQuit()) {
        quit = false;
        window.close();
    }

    Play->Update(window, mousePos);
    Options->Update(window, mousePos);
    Exit->Update(window, mousePos);

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {

            if (Play->button_state == HOVER) Play->button_state = PRESSED;
            if (Options->button_state == HOVER) Options->button_state = PRESSED;
            if (Exit->button_state == HOVER) Exit->button_state = PRESSED;
        }
    }
    _cloud1.move(-cloud_speed * dt, 0.f);
    _cloud2.move(-cloud_speed * dt, 0.f);
    _tumble.move(-tumble_speed * dt, 0.f);
    _tumble.rotate(-tumble_speed * dt);
    if (_cloud1.getPosition().x < -300) _cloud1.setPosition(CLOUD1_MX, CLOUD1_MY);
    if (_cloud2.getPosition().x < -300 - (CLOUD2_MX - CLOUD1_MX)) _cloud2.setPosition(CLOUD2_MX, CLOUD2_MY);
    if (_tumble.getPosition().x < -5000) _tumble.setPosition(TUMBLE_X, TUMBLE_Y);
}

void MainMenuState::Render() {
    window.draw(_background);
    window.draw(_cactus1);
    window.draw(_cactus3);
    window.draw(_cloud1);
    window.draw(_cloud2);
    window.draw(_tumble);

    window.draw(_cactus2);
    window.draw(_cactus4);

    window.draw(game_title);
    Play->Render(this->window);
    Options->Render(this->window);
    Exit->Render(this->window);
}

void MainMenuState::UpdateKeybinds(const float& dt) {
}

void MainMenuState::UpdateButtons() {
    

    if (Play->button_state == PRESSED) {
        this->states->push(new GameState(window, (this->states)));
    }

    if (Options->button_state == PRESSED) {
        this->states->push(new OptionsState(window, this->states));
    }

    if (Exit->button_state == PRESSED) {
        quit = true;
    }

}

void MainMenuState::UpdateInput(const float& dt) {}

