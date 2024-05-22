#include "network_io.h"
#include "game_engine.h"
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <vector>

NetworkIO::NetworkIO(GameEngine &gameEngineVal) : gameEngine(gameEngineVal) {
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

void NetworkIO::handleConnection(int connectionId, bool &running) {
  while (running) {
    // Send game state
    const char *gameState = nullptr; // Initialize to nullptr for safety
    auto it = gameEngine.observationPerConnection->find(connectionId);
    if (it != gameEngine.observationPerConnection->end()) {
      gameState = it->second.c_str();
    } else {
      gameState = "UNKNOWN";
    }

    if (send(connectionId, gameState, strlen(gameState), 0) == -1) {
      std::cout << "ERR: cannot send data through socket " << connectionId
                << std::endl;
      continue;
    }

    // Receive confirmation
    char response[512];
    int bytesReceived = recv(connectionId, response, sizeof(response) - 1, 0);
    if (bytesReceived == -1) {
      std::cout << "ERR: cannot receive data from socket " << connectionId
                << std::endl;
      continue;
    }
    response[bytesReceived] = '\0'; // Ensure null termination

    std::string action = response;
    if (action.length() > 0) {
      gameEngine.onNewNetworkAction(connectionId, action);
    }
  }

  // Close the connection socket
  close(connectionId);
}

void NetworkIO::run(bool &running) {
  // listen & wait for connections
  listen(serverSocket, 5);
  std::vector<int> connections;
  std::vector<std::thread> threads; // Store threads for joining later

  for (int i = 0; i < connectionsLimit; i++) {
    std::cout << "WAITING FOR CONNECTION " << i + 1 << std::endl;
    int newConnectionId = accept(serverSocket, nullptr, nullptr);
    connections.push_back(newConnectionId);
    if (onNewConnection) {
      onNewConnection(newConnectionId);
    }

    // Create a new thread for the connection
    threads.emplace_back([&]() { handleConnection(newConnectionId, running); });
  }

  // Wait for all threads to finish before sending "done" state
  for (auto &thread : threads) {
    thread.join(); // Wait for each thread to complete
  }

  const char *doneState = "done";
  for (auto &connection : connections) {
    send(connection, doneState, strlen(doneState), 0);
  }

  // closing the socket.
  close(serverSocket);
}
