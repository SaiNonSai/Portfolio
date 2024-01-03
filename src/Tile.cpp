
#include "Tile.h"

Tile::Tile()
{
  tile_sprite = std::make_unique<sf::Sprite>();
}

Tile::Tile(const int& ID, const sf::Texture& texture) : Tile()
{
  tile_ID = ID;
  tile_sprite->setTexture(texture);
}

std::unique_ptr<sf::Sprite>& Tile::getSprite()
{
  return tile_sprite;
}

int Tile::getID() const
{
  return tile_ID;
}