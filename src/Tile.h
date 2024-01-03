#ifndef SFMLGAME_TILE_H
#define SFMLGAME_TILE_H

#include <SFML/Graphics.hpp>

class Tile
{
 public:
  Tile();
  Tile(const int& ID, const sf::Texture& texture);
  ~Tile() = default;
  std::unique_ptr<sf::Sprite>& getSprite();
  int getID() const;

 private:
  int tile_ID = 0;
  std::unique_ptr<sf::Sprite> tile_sprite;
};

#endif // SFMLGAME_TILE_H
