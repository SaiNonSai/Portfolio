//
// Created by sl2-non on 06/12/2023.
//
#include "Villager.h"
#include <iostream>

Villager::Villager(sf::RenderWindow& game_window): window(game_window)
{

}

void Villager::init()
{
  //text
  font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf");
  bubble_text.setFont(font);
  bubble_text.setString("WELCOME TO LITTLE \n"
                        "TOWN,"
                        "HAVE FUN EXPLORING \n "
                        "THE TOWN");
  bubble_text.setCharacterSize(10);
  bubble_text.setScale(zoom, zoom);
  bubble_text.setFillColor(sf::Color::Black);
  bubble_text.setPosition(350,283);

  //background
  bubble_txt.loadFromFile("Data/Images/Bubble.png");
  bubble.setTexture(bubble_txt);
  bubble.setScale(0.05, 0.05);
  bubble.setPosition(348 , 280);

}

void Villager::render()
{
  window.draw(bubble);
  window.draw(bubble_text);
}
