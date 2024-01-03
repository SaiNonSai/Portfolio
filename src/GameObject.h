//
// Created by Sai on 12/5/2023.
//

#ifndef SFMLGAME_GAMEOBJECT_H
#define SFMLGAME_GAMEOBJECT_H
#include <SFML/Graphics.hpp>


class GameObject
{
 public:
  GameObject();
  GameObject(sf::Text text);
  GameObject(sf::Sprite sprite);
  ~GameObject();

  bool isVisible() const;
  void setIsVisible(bool isVisible);




 private:

  bool is_visible = false;


};
#endif // SFMLGAME_GAMEOBJECT_H
