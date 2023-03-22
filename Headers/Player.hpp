#include <deque>
#include <memory>

#include "Global.hpp"
#include "Obsticle.hpp"


#include <SFML/Graphics.hpp>

enum PlayerState {
    RUNNING = 0,
    DOWN,
    JUMPING,
    DEAD
};

class Player {
    public:

    Player(sf::RenderWindow& window);

    void Init();

    void Scale();

    void Update(const float& dt, const float& game_speed);

    void Render(sf::RenderWindow& window);

    void CheckColisions(std::deque<std::shared_ptr<Obsticle>>& obsticles);

        sf::RenderWindow& window;
        sf::Sprite _player;
        sf::Event event;
    
        PlayerState player_state;

        float timer;
        int y;
        float velocity_y = 0;
        const float gravity_y = 0.35;
        
};

