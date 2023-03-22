#include <iostream>

#include "Game.hpp"
#include "TextureManager.hpp"
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "State.hpp"

Game::Game() {
    InitWindow();
    InitStates();
    dt = 0.f;
}
    
Game::~Game() {
    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}

void Game::InitStates() {
    this->states.push(new MainMenuState(window, &(this->states)));
}

void Game::InitWindow() {
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Dino run", sf::Style::Fullscreen);
    window.setKeyRepeatEnabled(false);
}

void Game::Update() {
    UpdateEvents();
    if (!this->states.empty()) {
        this->states.top()->Update(dt);

        if(this->states.top()->getQuit()) {
            delete states.top();
            states.pop();
        }
    }
}
        
void Game::Render() {
    this->window.clear();
    if (!this->states.empty()) {
        this->states.top()->Render();
    }
    this->window.display();
}

void Game::Run() {
   
    while (this->window.isOpen()) {
        UpdateDt();
        Update();
        Render();
    }
}


void Game::UpdateEvents() {
}

void Game::UpdateDt() {
    //Updates dt with time it takes to update and render one frame
    this->dt = this->dtClock.restart().asSeconds();
}


