//
// Created by Sai on 12/5/2023.
//
#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
  {

  };

GameObject::~GameObject()
  {

  };

bool GameObject::isVisible() const
{
  return is_visible;
}
void GameObject::setIsVisible(bool isVisible)
{
  is_visible = isVisible;
}
GameObject::GameObject(sf::Text text)
{

}
GameObject::GameObject(sf::Sprite sprite)
{

}
