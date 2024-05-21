#include "network_io.h"
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

NetworkIO::NetworkIO() {
  port = 9889;
  connectionsLimit = 2;
}

void NetworkIO::setup() {
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  // specifying the address
  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(port);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  // binding socket.
  if (bind(serverSocket, (struct sockaddr *)&serverAddress,
           sizeof(serverAddress)) > 0) {
    std::cout << "ERR: something went wrong!. Cannot bind socket";
    exit(1);
    return;
  }
}

void NetworkIO::setOnNewConnectionCallback(std::function<void(int)> callback) {
  onNewConnection = callback;
}

void NetworkIO::run(bool &running) {
  // listen & wait for connections
  listen(serverSocket, 5);
  for (int i = 0; i < connectionsLimit; i++) {
    std::cout << "WAITING FOR CONNECTION " << i + 1 << std::endl;
    int newConnectionId = accept(serverSocket, nullptr, nullptr);
    connections.push_back(newConnectionId);
    if (onNewConnection) {
      onNewConnection(newConnectionId);
    }
  }

  // run the main loop ( based on gameEngine.running )
  while (running) {
    const char *gameState = "{1, 2, 3, 4}";
    for (auto &connection : connections) {
      if (send(connection, gameState, strlen(gameState), 0) == -1) {
        std::cout << "ERR: cannot send data through socket" << std::endl;
        running = false;
        break;
      }
    }
  }

  const char *doneState = "done";
  for (auto &connection : connections) {
    send(connection, doneState, strlen(doneState), 0);
  }

  // closing the socket.
  close(serverSocket);
}
