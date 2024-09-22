#include <iostream>
#include <stdexcept>
#include <SFML/Graphics.hpp>

enum GameMode {
    CUTSCENE,
    BATTLE,
    PAUSE,
    MENU,
}; 

class Game {
private:
    void cutscene_load() {}
    void battle_load() {}
    void pause_load() {}
    void menu_load() {}

    void cutscene_draw() {}
    void battle_draw() {}
    void pause_draw() {}
    void menu_draw() {}

    struct Cutscene {} cutscene;
    struct Battle {} battle;
    struct Pause {} pause;
    struct Menu {} menu;

public:
    Game() {
        mode = GameMode::MENU;

        if (!whiteboard.loadFromFile(ASSET_DIR "/whiteboard.ttf")) {
            throw std::runtime_error("whiteboard font could not load!");
        }
    }

    ~Game() {}

    void cutscene_update() {}
    void battle_update() {}
    void pause_update() {}
    void menu_update() {}

    GameMode mode;
    sf::Font whiteboard;
};

int main() {
    Game game;

    while (true) {
        switch (game.mode) {
        case GameMode::CUTSCENE :
            game.cutscene_update();
            break;

        case GameMode::BATTLE :
            game.battle_update();
            break;

        case GameMode::PAUSE :
            game.pause_update();
            break;

        case GameMode::MENU :
            game.menu_update();
            break;
        }
    } 
}