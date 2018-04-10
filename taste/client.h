#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "inbox.h"
#include "message.h"

class Client {
 public:
  Client(std::string name, Inbox<Client> & inbox); 
  void send(Message & msg);
  void recv(Message & msg);
  std::string get_name(); 
 private:
  std::string name;
  Inbox<Client> & inbox;
};

#endif
