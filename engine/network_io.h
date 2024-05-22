
#ifndef NETWORK_IO_H
#define NETWORK_IO_H

#include <functional>
#include <vector>

class GameEngine; // just to forward-declare

class NetworkIO {
public:
  NetworkIO(GameEngine &gameEngineVal);
  void setup();
  void run(bool &running, std::string *endingMessage);
  void setOnNewConnectionCallback(std::function<void(int)> callback);

  int connectionsLimit;

private:
  void handleConnection(int connectionId, bool &running,
                        std::string *endingMessage);

  int serverSocket;
  int port;
  std::vector<int> connections;
  std::function<void(int)> onNewConnection;
  GameEngine &gameEngine;
};

#endif // !NETWORK_IO_H
