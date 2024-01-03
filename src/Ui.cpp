//
// Created by Sai on 12/5/2023.
//
#include "Ui.h"

UI::UI(sf::RenderWindow& game_window) : window(game_window)
{

}
void UI::init()
{
  camera = std::make_shared<sf::View>(sf::FloatRect(0,0, window.getSize().x, window.getSize().y));
  camera->zoom(zoom);
  window.setView(*camera);

  if(!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "Font failed to load";
  }
  //background
  background_txt = std::make_unique<sf::Texture>();
  background_txt->loadFromFile("Data/Images/inventory.png");

  bg = std::make_unique<sf::Sprite>();
  bg->setTexture(*background_txt);
  bg->setScale(0.5, 0.5);


  //inventory text
  inventory = std::make_unique<sf::Text>();
  inventory->setFont(font);
  inventory->setString("Inventory");
  inventory->setCharacterSize(30);
  inventory->setScale(zoom, zoom);

  //init item sprite
  item_collected = false;
  item = std::make_unique<sf::Sprite>();
  item_texture = std::make_unique<sf::Texture>();
  if(!item_texture->loadFromFile("Data/Images/player.png"))
  {
    std::cout << "Texture failed to load";
  }
  item->setTexture(*item_texture);
  item->setTextureRect(sf::IntRect(144, 144, 16, 16));
  item->setPosition(200, 500);
}

void UI::update(sf::Vector2f center_camera, sf::Sprite& player)
{
  bg->setPosition(center_camera);
  bg->move(40,-60);

  inventory->setPosition(center_camera);
  inventory->move(50, -50);

  camera->setCenter(center_camera);
  window.setView(*camera);

  if(item->getGlobalBounds().intersects(player.getGlobalBounds()))
  {
    item_collected = true;
  }
  if(item_collected)
  {
    item->setPosition(inventory->getPosition());
    item->move(inventory->getGlobalBounds().width - item->getGlobalBounds().width,
               item->getGlobalBounds().height + 3 );
  }


}

void UI::render()
{
  window.draw(*bg);
  window.draw(*inventory);
  window.draw(*item);
}

