#include "State.hpp"
#include "Global.hpp"
#include "TextureManager.hpp"
#include <SFML/Graphics.hpp>

class OptionsState : public State {
    public:
        OptionsState(sf::RenderWindow& w, std::stack<State*>* state);
    
        void Init();

        void Update(const float& dt);

        void Render();

        void UpdateInput(const float& dt);

    private:
        sf::Sprite _background;
        sf::Sprite _cloud1;
        sf::Sprite _cloud2;
        sf::Sprite _cactus1;
        sf::Sprite _cactus2;
        sf::Sprite _cactus3;
        sf::Sprite _cactus4;
        sf::Sprite _cactus5;

        sf::Text Title;
        sf::Text Jump;
        sf::Text BendDown;
        sf::Text JumpKeys;
        sf::Text BendDownKeys;
        sf::Text Pause;
        sf::Text PauseKeys;
        
        float cloud_speed = 80;
};
