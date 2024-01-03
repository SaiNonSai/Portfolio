
#include "Game.h"
#include "Ui.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window, bool server)
  : window(game_window), isServer(server)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  init_tmx();
  // menu
  in_menu = true;
  if(!font.loadFromFile("Data/Fonts/OpenSans-LightItalic.ttf"))
  {
    std::cout << "text did not load \n";
    return false;
  }
  //background
  if(!background_texture.loadFromFile("Data/Images/Map.png"))
  {
    std::cout << "background did not load \n";
    return false;
  }
  background.setTexture(background_texture);
  background.setScale(1.5 ,1.7);

  //Title
  Title.setString("Network SFML");
  Title.setFont(font);
  Title.setCharacterSize(200);
  Title.setFillColor(sf::Color::White);
  Title.setPosition(window.getSize().x / 2 - Title.getGlobalBounds().width / 2,
                    window.getSize().y / 2 - Title.getGlobalBounds().height / 2);
  //Start
  Start.setString("Start");
  Start.setFont(font);
  Start.setCharacterSize(100);
  Start.setFillColor(sf::Color::White);
  Start.setPosition(500, 700);

  //Quit
  Quit.setString("Quit");
  Quit.setFont(font);
  Quit.setCharacterSize(100);
  Quit.setFillColor(sf::Color::White);
  Quit.setPosition(1200, 700);

  //Villager
  if(!villager_texture.loadFromFile("Data/Images/player.png"))
  {
    std::cout << "villager did not load \n";
    return false;
  }
  villager.setTexture(villager_texture);
  villager.setTextureRect(sf::IntRect(16, 112, 16, 16));
  villager.setPosition(336,300);

  //weapon
  if(!weapon_texture.loadFromFile("Data/Images/player.png"))
  {
    std::cout << "weapon did not load \n";
  }
  weapon.setTexture(weapon_texture);
  weapon.setTextureRect(sf::IntRect(130, 128, 16, 16));
  weapon.setPosition(400,500);

  //chest
  if(!chest_texture.loadFromFile("Data/Images/player.png"))
  {
    std::cout << "chest did not load \n";
  }
  chest.setTexture(chest_texture);
  chest.setTextureRect(sf::IntRect(80, 112, 16, 16));
  chest.setPosition(500,400);

  //villager text
  /*bubble_text = std::make_unique<sf::Text>();
  bubble_text->setFont(font);
  bubble_text->setString("WELCOME TO LITTLE \n"
                         "TOWN,"
                         "HAVE FUN EXPLORING \n "
                         "THE TOWN");
  bubble_text->setCharacterSize(5);
  bubble_text->setFillColor(sf::Color::Black);
  bubble_text->setPosition(villager.getPosition().x + 12 , villager.getPosition().y - 20);

  bubble.setSize(sf::Vector2f(65,20));
  bubble.setFillColor(sf::Color::White);
  bubble.setPosition(villager.getPosition().x + 10, villager.getPosition().y - 20);*/



  if (isServer)
  {
    server = std::make_unique<Server>();
    server->init();
    server->run();
  }
  else
  {
      client = std::make_unique<Client>(window);
      client->connect();
      client->run();
      client->init();
  }
  return true;
}

void Game::init_tmx()
{
  tmx::Map map;
  if (!tilemap->loadFromFile("Data/Images/tilemap_packed.png"))
  {
    std::cout << "Error: Fail to load spritesheet!" << std::endl;
  }
  if (!map.load("Data/Images/Map.tmx"))
  {
    std::cout << "Error: Fail to load map data!" << std::endl;
  }

  const unsigned int MAP_COLUMNS = map.getTileCount().x;
  const unsigned int MAP_ROWS = map.getTileCount().y;

  auto& tile_size = map.getTileSize();
  TILE_MAP.reserve(map.getLayers().size());

  for (const auto& layer : map.getLayers())
  {
    TILE_MAP.emplace_back(std::vector<std::unique_ptr<Tile>>());
    const auto& tiles = layer->getLayerAs<tmx::TileLayer>().getTiles();
    TILE_MAP.back().reserve(tiles.size());
    for (const auto& tile : tiles)
    {
      SetTileWithID(MAP_COLUMNS, tile_size, tile);
    }
  }
}

void Game::update(float dt)
{
  if (!isServer)
  {
    client->update(dt, TILE_MAP, weapon, chest, villager);
  }
}

void Game::render()
{
    if (!isServer)
    {
      if(in_menu)
      {
        camera = window.getDefaultView();
        camera.zoom(1);
        window.setView(camera);
        window.draw(background);
        window.draw(Title);
        window.draw(Start);
        window.draw(Quit);
      }
      else
      {
        client->render(TILE_MAP);
        window.draw(villager);
        window.draw(weapon);
        window.draw(chest);
      }
    }

}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::keyPressed(sf::Event event)
{
  if(
    (event.key.code == sf::Keyboard::A) ||
    (event.key.code == sf::Keyboard::D))
  {
      selected = !selected;
      if (selected)
      {
        Start.setString("> Start <");
        Quit.setString("Quit");
      }
      else
      {
        Start.setString("Start");
        Quit.setString(" > Quit <");
      }
  }
  else if (event.key.code == sf::Keyboard::Enter)
  {
      if (selected)
      {
        in_menu = false;
      }
      else
      {
        window.close();
      }
  }
  if (!isServer)
  {
    client->keyPressed(event, weapon, villager);
  }
}

void Game::keyReleased(sf::Event event)
{
  if (!isServer)
  {
    client->keyReleased(event);
  }
}

void Game::SetTileWithID(const unsigned int MAP_COLUMNS, const tmx::Vector2u& tile_size, const tmx::TileLayer::Tile& tile)
{
  auto& current = *TILE_MAP.back().emplace_back(std::make_unique<Tile>(tile.ID, *tilemap));

  int x = current.getID();
  if (x > 0)
  {
    int y = floor((x - 1) / SPRITESHEET_X);
    x = (x - 1) % SPRITESHEET_X;
    current.getSprite()->setTextureRect(sf::IntRect(x * 16, y * 16, 16, 16));
    /**sf::IntRect((current.getID() * tile_size.x) - tile_size.x, 0, tile_size.x, tile_size.y)**/
  }
  current.getSprite()->setPosition(((TILE_MAP.back().size()-1) % MAP_COLUMNS) * tile_size.x, ((TILE_MAP.back().size()-1) / MAP_COLUMNS) * tile_size.y);
}
