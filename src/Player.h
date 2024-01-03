
#ifndef SFMLGAME_PLAYER_H
#define SFMLGAME_PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <tuple>
#include "Vector.h"

class Player
{
 public:
  void init();
  void update(float dt);
  sf::Vector2f getSpriteCentre();
  std::unique_ptr<sf::Sprite>& getSprite();

  Vector direction = Vector(0, 0);
  const int SPEED = 100;

 private:


  float player_distance = 2.0f;
  std::unique_ptr<sf::Sprite> sprite;
  std::unique_ptr<sf::Texture> texture;



};

#endif // SFMLGAME_PLAYER_H
