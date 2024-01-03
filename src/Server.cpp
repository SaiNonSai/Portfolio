
#include "Server.h"

void Server::init()
{
  if (listener == nullptr)
  {
    listener = std::make_unique<sf::TcpListener>();
  }
  if (listener->listen(53000) != sf::Socket::Done)
  {

  }
}

void Server::run()
{
  while (running)
  {
    sf::TcpSocket& cSock =
      connections.emplace_back(std::make_unique<sf::TcpSocket>()).operator*();
    if (listener->accept(cSock) != sf::Socket::Done)
    {
      connections.pop_back();
      return;
    }
    std::cout << "Client connected @" << cSock.getRemotePort() << std::endl;
    workers.emplace_back([&]{
                           listen(cSock);
                         });
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::cout << "detected disconnect\n";
    std::lock_guard<std::mutex>lck(mutex);

    for (int i = 0; i < connections.size(); ++i)
    {
      if (connections[i]->getLocalPort() == cSock.getLocalPort())
      {
        continue;
      }
      connections.erase(std::next(connections.begin(), i));
      break;
    }
  }
}

void Server::listen(sf::TcpSocket& cSocket)
{
  bool continue_receiving = true;

  char data[1028];
  std::size_t received;

  while (continue_receiving)
  {
    auto status = cSocket.receive(data, 1028, received);
    if (status == sf::Socket::Status::Disconnected)
    {
      continue_receiving = false;
      std::cout << "Disconnected." << std::endl;
    }
    if (received < 1028)
    {
      data[received] = '\0';
    }
    send(data);
    std::cout << reinterpret_cast<char*>(data) << '\n';
  }
  cSocket.disconnect();
}

void Server::send(std::string buffer)
{;
  auto message = reinterpret_cast<char*>(buffer.data());

  std::lock_guard<std::mutex>lck(mutex);

  for (auto & connection: connections)
  {
      connection->send(message, buffer.size());
  }
}

