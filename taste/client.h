#ifndef CLIENT_H
#define CLIENT_H

#include <random>
#include <string>
#include "inbox.h"
#include "message.h"

class Client {
 public:
  Client(std::string name, Inbox<Client>& inbox, unsigned seed);
  void send(Message& msg);
  void recv(Message& msg);
  std::string get_name();

 private:
  std::string name;
  Inbox<Client>& inbox;
  std::uniform_int_distribution<int> dist;
  std::mt19937 gen;
};

#endif
