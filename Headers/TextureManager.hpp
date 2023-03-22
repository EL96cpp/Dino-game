#pragma once

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

class TextureManager {
    public:
        void LoadTexture (std::string name, std::string filePath);
        sf::Texture& GetTexture(std::string name);
        
        void LoadFont (std::string name, std::string filePath);
        sf::Font& GetFont(std::string name);

        static TextureManager& instance();

    private:
        TextureManager() {}

        TextureManager(TextureManager&);
        TextureManager& operator = (TextureManager&);

        std::map<std::string, sf::Texture> _textures;
        std::map<std::string, sf::Font> _fonts;
};
