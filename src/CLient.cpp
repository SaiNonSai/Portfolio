
#include "Client.h"
#include "GameObject.h"

Client::Client(sf::RenderWindow& game_window) : window(game_window)
{

}

void Client::connect()
{
  if (socket == nullptr)
  {
    socket = std::make_unique<sf::TcpSocket>();
  }
  if (socket->connect("127.0.0.1", 53000) == sf::Socket::Status::Done)
  {
    std::cout << " You're Connected!" << std::endl;
    connected = true;
  }
  else
  {
    std::cout << " failed to connect";
  }
}

void Client::input(sf::TcpSocket& iSocket) const
{
  while (running)
  {
    //std::string str;
    //str = msg_txt.getString();
    //std::getline(std::cin, str);
    std::cin.clear();
    if (connected)
    {
      //iSocket.send(reinterpret_cast<char*>(str.data()), str.length());
    }
  }
}

void Client::run()
{
  running = true;
  std::thread input_thread([&] { input(*socket); });
  input_thread.detach();
  std::thread run_threads(([&] { runThreads(); }));
  run_threads.detach();
}

void Client::runThreads()
{
  while (running && connected)
  {
    char static_buffer[1028];
    while (connected)
    {
      std::size_t received;
      auto status = socket->receive(static_buffer, 1028, received);

      if (status == sf::Socket::Status::Disconnected)
      {
        connected = false;
        std::cout << "clean disconnection" << std::endl;
        socket->disconnect();
        break;
      }
      else
      {
        if (received < 1028)
        {
          static_buffer[received] = '\0';
        }
        std::cout << static_buffer << '\n';

        for(int i = 9; i > 1; i--)
        {
          msg_txt[i].setString(msg_txt[i - 1].getString());
        }
        msg_txt[1].setString(static_buffer);
      }
    }
  }
}

// GamePlay
void Client::init()
{

  camera = window.getDefaultView();
  camera.zoom(0.2f);
  window.setView(camera);
  player.init();
  ui.init();
  villager_txt.init();

  //message box
  msg_font.loadFromFile("Data/Fonts/OpenSans-LightItalic.ttf");
  for(int i = 0; i < 10; i++)
  {
    msg_txt[i].setFont(msg_font);
    msg_txt[i].setScale(0.2,0.2);
  }


}

void Client::update(float dt, std::vector<std::vector<std::unique_ptr<Tile>>>& TILE_MAP,
                    sf::Sprite& weapon, sf::Sprite& villager,sf::Sprite& chest)
{
  //str = msg_txt.getString();
  camera.setCenter(player.getSpriteCentre());
  window.setView(camera);
  for(int i = 0; i < 10; i++)
  {
    msg_txt[i].setPosition(player.getSpriteCentre().x, player.getSpriteCentre().y - 20 - i * 5);
  }


  ui.update(camera.getCenter(), *player.getSprite());

  // weapons
  if(weapon_pickup)
  {
    weapon.setPosition(player.getSprite()->getPosition().x, player.getSprite()->getPosition().y);
    weapon.move(-10,0);
  }
  else
  {
    if(weapon.getGlobalBounds().intersects(player.getSprite()->getGlobalBounds()))
    {
      weapon_pickup = true;
    }
  }

  //villager
  if (villager.getGlobalBounds().intersects(player.getSprite()->getGlobalBounds()))
  {
    //villager text appear
    std::tuple<float, float> temp = player.direction.getNormalised();
    player.getSprite()->move(-(std::get<0>(temp) * 100 * dt), -(std::get<1>(temp) * 100 * dt));
    player.direction.setX(0);
    player.direction.setY(0);
  }
  //chest
  if(chest.getGlobalBounds().intersects(player.getSprite()->getGlobalBounds()))
  {
    //open inventory
    std::tuple<float, float> temp = player.direction.getNormalised();
    player.getSprite()->move(-(std::get<0>(temp) * 100 * dt), -(std::get<1>(temp) * 100 * dt));
    player.direction.setX(0);
    player.direction.setY(0);
  }
  //text_box
  if(!text_open)
  {
    player.update(dt);
  }

  for (const auto& tile : TILE_MAP[0])
  {
    if (tile->getID() == 2)
    {
      if(tile->getSprite()->getGlobalBounds().intersects(player.getSprite()->getGlobalBounds()))
      {
        std::cout << "collide" << std::endl;
        std::tuple<float, float> temp = player.direction.getNormalised();
        player.getSprite()->move(-(std::get<0>(temp) * 100 * dt), -(std::get<1>(temp) * 100 * dt));
        player.direction.setX(0);
        player.direction.setY(0);
      }
    }
  }
}

void Client::render(std::vector<std::vector<std::unique_ptr<Tile>>>& TILE_MAP)
{
  window.clear(sf::Color::Black);
  for (const auto& layer : TILE_MAP)
  {
    for (const auto& tile : layer)
    {
      if (tile->getID() > 0)
      {
        window.draw(*tile->getSprite());
      }
    }
  }
  if(inventory_open)
  {
    ui.render();
  }
  if(text_open)
  {
    villager_txt.render();
  }
  window.draw(*player.getSprite());
  for(int i = 0; i < 10; i++)
  {
    window.draw(msg_txt[i]);
  }


}

void Client::keyPressed(sf::Event event, sf::Sprite& weapon, sf::Sprite& villager)
{

  if(event.key.code == sf::Keyboard::Tab)
  {
    //if(villager.getGlobalBounds().intersects(player.getSprite()->getGlobalBounds()))
    //{
      text_open = !text_open;
    //}
  }

  if(!text_open)
  {
    if (event.key.code == sf::Keyboard::W)
    {
      player.direction.setY(-1);
    }
    else if (event.key.code == sf::Keyboard::S)
    {
      player.direction.setY(1);
    }
    if (event.key.code == sf::Keyboard::A)
    {
      player.direction.setX(-1);
    }
    else if (event.key.code == sf::Keyboard::D)
    {
      player.direction.setX(1);
    }
    if(event.key.code == sf::Keyboard::G)
    {
      if(weapon_pickup == true)
      {
        weapon_pickup = false;
        weapon.move(-20, 0);
      }
    }
    if(event.key.code == sf::Keyboard::I)
    {
      inventory_open = !inventory_open;
    }
  }
  else
    if(event.key.code == sf::Keyboard::Enter)
    {
      socket->send(reinterpret_cast<char*>(txt_input.data()), txt_input.length());
      txt_input = "";
      text_open = false;
      msg_txt[0].setString("");
    }
}

void Client::keyReleased(sf::Event event)
{
  if (event.key.code == sf::Keyboard::W)
  {
    player.direction.setY(0);
  }
  else if (event.key.code == sf::Keyboard::S)
  {
    player.direction.setY(0);
  }
  if (event.key.code == sf::Keyboard::A)
  {
    player.direction.setX(0);
  }
  else if (event.key.code == sf::Keyboard::D)
  {
    player.direction.setX(0);
  }
}

void Client::TextEntered(sf::Event event)
{
  if(text_open)
  {
    if(event.text.unicode < 128)
    {
      //8 = backspace key
      if (event.text.unicode == 8)
      {
        if (txt_input.size() > 0)
        {
          txt_input.pop_back();
        }
      }
      // 27 = escape key
      else if (event.text.unicode != 27)
      {
        txt_input += static_cast<char>(event.text.unicode);
      }
    }

    msg_txt[0].setString(txt_input);
  }


}

