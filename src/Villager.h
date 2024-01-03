//
// Created by sl2-non on 06/12/2023.
//

#ifndef SFMLGAME_VILLAGER_H
#define SFMLGAME_VILLAGER_H
#include <SFML/Graphics.hpp>
#include <memory>

class Villager
{
 public:
  Villager(sf::RenderWindow& game_window);
  void init();
  void update(sf::Vector2f camera_center);
  void render();


 private:
  sf::RenderWindow& window;
  std::shared_ptr<sf::View> camera;
  const float zoom = 0.2f;


  sf::Font font;
  sf::Text bubble_text;
  sf::Texture bubble_txt;
  sf::Sprite bubble;


};

#endif // SFMLGAME_VILLAGER_H
