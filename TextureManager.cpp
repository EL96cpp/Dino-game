#include "TextureManager.hpp"

TextureManager& TextureManager::instance() {
    static TextureManager tm;
    return tm;
}



void TextureManager::LoadTexture(std::string name, std::string filePath) {
    sf::Texture tex;

    //был if
    tex.loadFromFile(filePath);
    _textures[name] = std::move(tex);
    
}

sf::Texture& TextureManager::GetTexture(std::string name) {
    return _textures.at(name);
}

void TextureManager::LoadFont(std::string name, std::string filePath) {
    sf::Font font;
    if (font.loadFromFile(filePath)) {
        _fonts[name] = std::move(font);
    }
}

sf::Font& TextureManager::GetFont(std::string name) {
    return _fonts.at(name);
}
