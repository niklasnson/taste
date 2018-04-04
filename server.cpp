#include "server.h"

Server::Server() {
}

void
Server::recive(Package &package) {
  package.identify();
}

void 
Server::send(Package &package) {
}

bool 
Server::connected() { 
  return true; 
}
