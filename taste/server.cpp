#include "server.h"

Server::Server() {
}

void
Server::recive(Package &package) {
  log.push_back(package);
}

void 
Server::send(Package &package) {
}

bool 
Server::connected() { 
  return true; 
}

std::vector<Package> 
Server::get_log() {
  return log; 
}
