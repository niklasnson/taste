#ifndef CLIENT_H
#define CLIENT_H

#include "package.h"
#include "server.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

class Client {
 public:
  Client(); 
  Client(Server &server);
  void recive(Package &package); 
  void send(Package &package); 
  void send_packages(int num);  
  void send_unorded_packages(int num);
  bool connected(); 
 private:
  Server server; 
};

#endif