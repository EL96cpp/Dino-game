#include "OptionsState.hpp"
#include <SFML/Graphics.hpp>


OptionsState::OptionsState(sf::RenderWindow& w, std::stack<State*>* states) : State(w, states) {
    Init();
}

void OptionsState::Init() {
    
    TextureManager::instance().LoadTexture("Background2", BACKGROUND2_FILEPATH);
    
    Title.setFont(TextureManager::instance().GetFont("Font"));
    Jump.setFont(TextureManager::instance().GetFont("Font"));
    BendDown.setFont(TextureManager::instance().GetFont("Font"));
    JumpKeys.setFont(TextureManager::instance().GetFont("Font"));
    BendDownKeys.setFont(TextureManager::instance().GetFont("Font"));
    Pause.setFont(TextureManager::instance().GetFont("Font"));
    PauseKeys.setFont(TextureManager::instance().GetFont("Font"));



    Title.setStyle(sf::Text::Bold);
    Title.setCharacterSize(150);
    Title.setString("CONTROLS");
    Title.setFillColor(sf::Color::Black);
    Title.setOrigin(Title.getLocalBounds().width/2.f, Title.getLocalBounds().height/2.f);
    Title.setPosition(SCREEN_WIDTH/2, OPTIONS_TITLE_Y);

    Jump.setPosition(OPTIONS_X1, OPTIONS_TITLE_Y + 200);
    Jump.setCharacterSize(75);
    Jump.setString("Jump");
    Jump.setFillColor(sf::Color::Black);

    BendDown.setPosition(OPTIONS_X1, OPTIONS_TITLE_Y + OPTIONS_STEP_Y + 200);
    BendDown.setCharacterSize(75);
    BendDown.setString("Bend down");
    BendDown.setFillColor(sf::Color::Black);

    Pause.setPosition(OPTIONS_X1, OPTIONS_TITLE_Y + OPTIONS_STEP_Y * 2 + 200);
    Pause.setCharacterSize(75);
    Pause.setString("Pause");
    Pause.setFillColor(sf::Color::Black);

    JumpKeys.setCharacterSize(75);
    JumpKeys.setString("Spase, W, Up");
    JumpKeys.setFillColor(sf::Color::Black);
    JumpKeys.setOrigin(JumpKeys.getLocalBounds().width/2.f, 0);
    JumpKeys.setPosition(OPTIONS_X2, OPTIONS_TITLE_Y + 200);

    BendDownKeys.setCharacterSize(75);
    BendDownKeys.setString("S, Down");
    BendDownKeys.setFillColor(sf::Color::Black);
    BendDownKeys.setOrigin(BendDownKeys.getLocalBounds().width/2.f, 0);
    BendDownKeys.setPosition(OPTIONS_X2, OPTIONS_TITLE_Y + OPTIONS_STEP_Y + 200);

    PauseKeys.setCharacterSize(75);
    PauseKeys.setString("P");
    PauseKeys.setFillColor(sf::Color::Black);
    PauseKeys.setOrigin(PauseKeys.getLocalBounds().width/2.f, 0);
    PauseKeys.setPosition(OPTIONS_X2, OPTIONS_TITLE_Y + OPTIONS_STEP_Y * 2 + 200);

    _background.setTexture(TextureManager::instance().GetTexture("Background2"));
    _cactus1.setTexture(TextureManager::instance().GetTexture("Cactus2"));      
    _cactus2.setTexture(TextureManager::instance().GetTexture("Cactus3"));          
    _cactus3.setTexture(TextureManager::instance().GetTexture("Cactus3"));  
    _cactus4.setTexture(TextureManager::instance().GetTexture("Cactus3"));  
    _cactus5.setTexture(TextureManager::instance().GetTexture("Cactus2"));
    _cloud1.setTexture(TextureManager::instance().GetTexture("Cloud"));
    _cloud2.setTexture(TextureManager::instance().GetTexture("Cloud"));

    _cactus1.scale(1.4, 1.4);
    _cactus2.scale(3.8, 3.8);
    _cactus3.scale(1.7, 1.7);
    _cactus4.scale(3.2, 3.2);
    _cactus5.scale(2.7, 2.7);
    _cloud1.scale(3.6, 3.6);
    _cloud2.scale(3.8, 3.8);

    _cactus1.setPosition(1255, 680);
    _cactus2.setPosition(215, 675);
    _cactus3.setPosition(570, 658);
    _cactus4.setPosition(1530, 725);
    _cactus5.setPosition(870, 675);
    _cloud1.setPosition(CLOUD1_MX, CLOUD1_MY);
    _cloud2.setPosition(CLOUD2_MX, CLOUD2_MY);

}

void OptionsState::Update(const float& dt) {
    sf::Event event;
    while(window.pollEvent(event)) {
        
        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Escape) {
            quit = true;
        }

    }
	
    _cloud1.move(-cloud_speed * dt, 0.f);
    _cloud2.move(-cloud_speed * dt, 0.f);
    if (_cloud1.getPosition().x < -300) _cloud1.setPosition(CLOUD1_MX, CLOUD1_MY);
    if (_cloud2.getPosition().x < -300 - (CLOUD2_MX - CLOUD1_MX)) _cloud2.setPosition(CLOUD2_MX, CLOUD2_MY);
}

void OptionsState::Render() {

    window.draw(_background);
    window.draw(_cactus1);
    window.draw(_cactus2);
    window.draw(_cactus3);
    window.draw(_cactus4);
    window.draw(_cactus5);
    window.draw(_cloud1);
    window.draw(_cloud2);

    window.draw(Title);
    window.draw(Jump);
    window.draw(Pause);
    window.draw(BendDown);
    window.draw(JumpKeys);
    window.draw(BendDownKeys);
    window.draw(PauseKeys);

}

void OptionsState::UpdateInput(const float& dt) {} 
