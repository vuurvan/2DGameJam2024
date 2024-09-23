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

  void setPosition(float x, float y) {
    sprite.setPosition(x,y);
  }

  void draw(sf::RenderWindow& window) {
    window.draw(sprite);
  }

  bool checkClicked(sf::Vector2i click) {
    if (click.x >= sprite.getGlobalBounds().left
    && click.x <= sprite.getGlobalBounds().left+sprite.getGlobalBounds().width
    && click.y >= sprite.getGlobalBounds().top
    && click.y <= sprite.getGlobalBounds().top+sprite.getGlobalBounds().height) {
      return true;
    }
    return false;
  }
};

class Game {
private:
  void cutscene_load() {}
  void battle_load() {
    if (!battle.cat_texture.loadFromFile(ASSET_DIR "/textures/Kat1.jpeg")) {
      throw std::runtime_error("kat1 texture could not load!");
    }

    battle.cat.setTexture(battle.cat_texture);
    battle.cat.setPosition(0.0f,0.0f);
    battle.cat.setScale(0.1f, 0.1f);
  }
  void pause_load() {
    pause.greybox.setSize(sf::Vector2f(vm.width, vm.height));
    pause.greybox.setFillColor(sf::Color(255,255,255,128));
  }
  void menu_load() {
    // if (!menu.title_texture.loadFromFile(ASSET_DIR "/textures/buttonStock1.png")) {
    //   throw std::runtime_error("title texture could not load!");
    // }
    if (!menu.start.loadFromFile(ASSET_DIR "/textures/buttonStock1d.png")) {
      throw std::runtime_error("start button texture could not load!");
    }

    // menu.title.setTexture(menu.title_texture);

    menu.start.setPosition(100.0f, 100.0f);
  }

  void cutscene_draw() {}
  void battle_draw() {
    window.draw(battle.cat);
  }
  void pause_draw() {
    battle_draw();
    window.draw(pause.greybox);
  }
  void menu_draw() {
    menu.start.draw(window);
  }

  struct Cutscene {} cutscene;
  struct Battle {
    sf::Texture cat_texture;
    sf::Sprite cat;
  } battle;
  struct Pause {
    sf::RectangleShape greybox;
  } pause;
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

    cutscene_load();
    battle_load();
    pause_load();
    menu_load();
  }

  ~Game() {}

  void cutscene_update() {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    cutscene_draw();
  }
  void battle_update() {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Q) {
          std::cout << "paused!\n";
          mode = GameMode::PAUSE;
        }
      }
    }
    battle_draw();
  }
  void pause_update() {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Q) {
          std::cout << "unpaused!\n";
          mode = GameMode::BATTLE;
        }
      }
    }
    pause_draw();
  }
  void menu_update() {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::MouseButtonReleased) {
        if (menu.start.checkClicked(sf::Mouse::getPosition(window))) {
          std::cout << "start clicked!\n";
          mode = GameMode::BATTLE;
        }
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