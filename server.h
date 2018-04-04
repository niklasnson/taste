#ifndef SERVER_H
#define SERVER_H

#include "package.h"
#include <iostream> 

class Server {
 public:
  Server();
  void recive(Package &package); 
  void send(Package &package);
  bool connected();
 private:
};

#endif