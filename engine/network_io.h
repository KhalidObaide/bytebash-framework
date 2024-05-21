
#ifndef NETWORK_IO_H
#define NETWORK_IO_H

#include <functional>
#include <vector>
class NetworkIO {
public:
  NetworkIO();
  void setup();
  void run(bool &running);
  void setOnNewConnectionCallback(std::function<void(int)> callback);

  int connectionsLimit;

private:
  int serverSocket;
  int port;
  std::vector<int> connections;
  std::function<void(int)> onNewConnection;
};

#endif // !NETWORK_IO_H
