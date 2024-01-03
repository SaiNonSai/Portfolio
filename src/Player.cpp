//
// Created by sl2-non on 20/11/2023.
//

#include "Player.h"

void Player::init()
{
  sprite = std::make_unique<sf::Sprite>();
  texture = std::make_unique<sf::Texture>();
  if (!texture->loadFromFile("Data/Images/player.png"))
  {
    std::cout << " Error: Failed to load player texture.";
  }
  sprite->setTexture(*texture);
  sprite->setTextureRect(sf::IntRect(0, 112, 16, 16));
  sprite->setPosition(500,500);
}

void Player::update(float dt)
{
  std::tuple<float, float> temp = direction.getNormalised();
  sprite->move(std::get<0>(temp) * SPEED * dt, std::get<1>(temp) * SPEED * dt);
}

sf::Vector2f Player::getSpriteCentre()
{
  sf::Vector2f v2;
  v2.x = sprite->getPosition().x + sprite->getGlobalBounds().width / 2;
  v2.y = sprite->getPosition().y + sprite->getGlobalBounds().height / 2;
  return v2;
}

std::unique_ptr<sf::Sprite>& Player::getSprite()
{
  return sprite;
}

