
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include "Tile.h"
#include "Player.h"
#include "Server.h"
#include "Client.h"
#include "GameObject.h"
#include "Ui.h"


class Game
{
 public:
  Game(sf::RenderWindow& window, bool server);
  ~Game();
  bool init();
  void init_tmx();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  void TextEntered(sf::Event event);
  bool game_over;


 private:
  bool isServer = false;
  std::unique_ptr<Client> client = nullptr;
  std::unique_ptr<Server> server = nullptr;

  std::unique_ptr<sf::Texture> tilemap = std::make_unique<sf::Texture>();
  std::vector<std::vector<std::unique_ptr<Tile>>> TILE_MAP;


  void SetTileWithID(const unsigned int MAP_COLUMNS, const tmx::Vector2u& tile_size, const tmx::TileLayer::Tile& tile);
  const int SPRITESHEET_X = 12;
  const int SPRITESHEET_Y = 11;

  bool in_menu;
  sf::Text Title;
  sf::Text Start;
  sf::Text Quit;
  sf::Font font;
  sf::RenderWindow& window;
  sf::View camera;
  sf::Sprite background;
  sf::Texture background_texture;
  bool selected = true;

  sf::Sprite villager;
  sf::Texture villager_texture;

  sf::Sprite weapon;
  sf::Texture weapon_texture;

  sf::Sprite chest;
  sf::Texture chest_texture;


  //std::unique_ptr<sf::Text> bubble_text;
  //sf::RectangleShape bubble;






};

#endif // PLATFORMER_GAME_H
