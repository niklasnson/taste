#include "client.h"
#include "inbox.h"
#include <iostream>

Client::Client(std::string name, Inbox<Client> & inbox)
  :name{name} ,inbox(inbox)
  {}


void
Client::send(Message & msg) {
  inbox.recv(msg);
}

void
Client::recv(Message & msg) {
  std::cout << name << " rcv msg: " << msg.message << std::endl; 

  if (msg.message == "PING") {
    send(*(new Message{"PONG", name, msg.from})); 
  }
}

std::string
Client::get_name() {
  return name; 
}

