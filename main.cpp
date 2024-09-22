#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

enum GameMode {
    CUTSCENE,
    BATTLE,
    PAUSE,
    MENU,
}; 

class Game {
private:
    std::mutex safety;

    std::lock_guard<std::mutex> main_lock(safety);
    std::lock_guard<std::mutex> cutscene_lock(safety);
    std::lock_guard<std::mutex> battle_lock(safety);
    std::lock_guard<std::mutex> pause_lock(safety);
    std::lock_guard<std::mutex> menu_lock(safety);

    std::thread cutscene_thread;
    std::thread battle_thread;
    std::thread pause_thread;
    std::thread menu_thread;

    std::thread cutscene_loader;
    std::thread battle_loader;
    std::thread pause_loader;
    std::thread menu_loader;

    void cutscene_load() {}
    void battle_load() {}
    void pause_load() {}
    void menu_load() {}

    void cutsceneDraw() {}
    void battleDraw() {}
    void pauseDraw() {}
    void menuDraw() {}

    void cutsceneUpdate() {}
    void battleUpdate() {}
    void pauseUpdate() {}
    void menuUpdate() {}

    void cutscene() {
        cutscene_loader = std::thread(cutscene_load);
        cutscene_update.wait(cutscene_lock);
    }
    void battle() {
        battle_loader = std::thread(battle_load);
        battle_update.wait(battle_lock);
    }
    void pause() {
        pause_loader = std::thread(pause_load);
        pause_update.wait(pause_lock);
    }
    void menu() {
        menu_loader = std::thread(menu_load);
        menu_update.wait(menu_lock);
    }

public:
    Game() {
        mode = GameMode::MENU;

        cutscene_thread(cutscene);
        battle_thread(battle);
        pause_thread(pause);
        menu_thread(menu);

        while (!cutscene_loader.joinable() && !battle_loader.joinable() && pause_loader.joinable() && menu_loader.joinable()) {}

        cutscene_loader.join();
        battle_loader.join();
        pause_loader.join();
        menu_loader.join();

        cutscene_update.notify_one();
        battle_update.notify_one();
        pause_update.notify_one();
        menu_update.notify_one();
    }

    ~Game() {
        cutscene_thread.join();
        battle_thread.join();
        pause_thread.join();
        menu_thread.join();
    }

    GameMode mode;

    std::condition_variable cutscene_update;
    std::condition_variable battle_update;
    std::condition_variable pause_update;
    std::condition_variable menu_update;
};

int main() {
    Game game;

    while (true) {
        switch (game.mode) {
        case GameMode::CUTSCENE :
            game.cutscene_update.notify_one();
            break;

        case GameMode::BATTLE :
            game.battle_update.notify_one();
            break;

        case GameMode::PAUSE :
            game.pause_update.notify_one();
            break;

        case GameMode::MENU :
            game.menu_update.notify_one();
            break;
        }
    }
    
}