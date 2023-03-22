#include <sstream>
#include "EmptyState.hpp"
#include "Global.hpp"

#include <iostream>

EmptyState::EmptyState(GameDataRef data) : _data(data) {}

void EmptyState::Init() {
    _data->texture_manager.LoadTexture("Background", BACKGROUND_FILEPATH);
    
    _background.setTexture(_data->texture_manager.GetTexture("Background"));
}

void EmptyState::HandleInput() {
}

void EmptyState::Update(float dt) {
    
}

void EmptyState::Draw(float dt) {
    _data->window.draw(_background);
}
   
    
    


