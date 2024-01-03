//
// Created by Sai on 12/5/2023.
//

#ifndef SFMLGAME_UI_H
#define SFMLGAME_UI_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

class UI
{
 public:
  UI(sf::RenderWindow& game_window);
  void init();
  void update(sf::Vector2f center_camera, sf::Sprite& player);
  void render();

  bool item_collected;
 private:
  sf::RenderWindow& window;
  std::shared_ptr<sf::View> camera;
  const float zoom = 0.2f;


  sf::Font font;
  std::unique_ptr<sf::Text> inventory;
  std::unique_ptr<sf::Sprite> item;
  std::unique_ptr<sf::Sprite> bg;
  std::unique_ptr<sf::Texture> item_texture;
  std::unique_ptr<sf::Texture> background_txt;



};

#endif // SFMLGAME_UI_H
