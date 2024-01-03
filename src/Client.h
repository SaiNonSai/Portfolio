
#ifndef SFMLGAME_CLIENT_H
#define SFMLGAME_CLIENT_H

#include <SFML/Network.hpp>
#include <iostream>
#include <atomic>
#include <thread>
#include "Player.h"
#include "Tile.h"
#include "Ui.h"
#include "GameObject.h"
#include "Villager.h"

class Client
{
 public:
  Client(sf::RenderWindow& game_window);
  void connect();
  void input(sf::TcpSocket& iSocket) const;
  void run();
  void init();
  void update(
    float dt, std::vector<std::vector<std::unique_ptr<Tile>>>& TILE_MAP,
    sf::Sprite& weapon, sf::Sprite& villager, sf::Sprite& chest);
  void render(std::vector<std::vector<std::unique_ptr<Tile>>>& TILE_MAP);
  void keyPressed(sf::Event event, sf::Sprite& weapon, sf::Sprite& villager);
  void keyReleased(sf::Event event);
  bool collision(sf::IntRect object_1, sf::IntRect object_2);

  std::atomic<bool> running = false;
  std::atomic<bool> connected = false;


 private:

  sf::RenderWindow& window;

  //collision
  float object_1_left;
  float object_1_right;
  float object_1_bottom;
  float object_1_top;
  float object_2_left;
  float object_2_right;
  float object_2_bottom;
  float object_2_top;

  std::unique_ptr<sf::TcpSocket> socket;
  void runThreads();

  Player player;

  //weapon
  bool weapon_pickup = false;

  float distance = 5.0f;

  //villager
  Villager villager_txt = Villager(window);
  bool text_open = false;

  //UI
  UI ui = UI(window);
  bool inventory_open = false;


  //camera
  sf::View camera;

};

#endif // SFMLGAME_CLIENT_H
