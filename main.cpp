#include <iostream>
#include <stdexcept>
#include <SFML/Graphics.hpp>

enum GameMode {
  CUTSCENE,
  BATTLE,
  PAUSE,
  MENU,
};

// every button will have its own image evntually (title will too)
class Button {
private:
  sf::Texture texture;
  sf::Sprite sprite;
public:
  bool loadFromFile(const std::string &filename, const sf::IntRect &area = sf::IntRect()) {
    if (!texture.loadFromFile(filename, area)) {
      return false;
    }

    sprite.setTexture(texture);

    return true;
  }

  void setPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
  }

  void draw(sf::RenderWindow& window) {
    window.draw(sprite);
  }
};

class Game {
private:
  void cutscene_load() {}
  void battle_load() {}
  void pause_load() {}
  void menu_load() {
    if (!menu.title_texture.loadFromFile(ASSET_DIR "/textures/buttonStock1.png")) {
      throw std::runtime_error("title texture could not load!");
    }
    if (!menu.start.loadFromFile(ASSET_DIR "/textures/buttonStock1d.png")) {
      throw std::runtime_error("start button texture could not load!");
    }

    menu.title.setTexture(menu.title_texture);

    menu.start.setPosition(sf::Vector2f(100.0f, 100.0f));
  }

  void cutscene_draw() {}
  void battle_draw() {}
  void pause_draw() {}
  void menu_draw() {
    menu.start.draw(window);
  }

  struct Cutscene {} cutscene;
  struct Battle {} battle;
  struct Pause {} pause;
  struct Menu {
    sf::Texture title_texture;
    sf::Sprite title;
    Button start;
    Button quit;
  } menu;

  sf::Event event;

public:
  Game() {
    vm = sf::VideoMode(800, 640);
    window.create(vm, "2DGameJam 2024");
    mode = GameMode::MENU;

    if (!whiteboard.loadFromFile(ASSET_DIR "/whiteboard.ttf")) {
      throw std::runtime_error("whiteboard font could not load!");
    }

    menu_load();
  }

  ~Game() {}

  void cutscene_update() {}
  void battle_update() {}
  void pause_update() {}
  void menu_update() {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    menu_draw();
  }

  GameMode mode;
  sf::Font whiteboard;
  sf::VideoMode vm;
  sf::RenderWindow window;
};

int main() {
  Game game;

  while (game.window.isOpen()) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      game.window.close();
      return 0;
    }

    game.window.clear();

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

    game.window.display();
  }

  return 0;
}