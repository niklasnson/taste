#ifndef SERVER_H
#define SERVER_H

#include "package.h"
#include <iostream> 
#include <vector>
class Server {
 public:
  Server();
  void recive(Package &package); 
  void send(Package &package);
  bool connected();
  std::vector<Package> get_log(); 
 private: 
  std::vector<Package> log; 
};

#endif
