#include "client.h"

Client::Client(Server &server) : server(server) {}

void
Client::recive(Package &package) {
  package.identify();
}

void 
Client::send(Package &package) {
  server.recive(package);
}

void 
Client::send_packages(int num) {
  for (int i=0; i < num; i++) {
    Package package(i);
    send(package);
  }
}

void 
Client::send_unorded_packages(int num) {
  std::vector<Package> packages_list; 
  for (int i=0; i < num; i++) {
    packages_list.push_back(i);
  }

  std::random_device rd;
  std::mt19937 g(rd());

  std::shuffle(packages_list.begin(), packages_list.end(), g);

  for (auto package : packages_list) {
    send(package);
  } 
}

bool 
Client::connected() {
  return server.connected(); 
}
