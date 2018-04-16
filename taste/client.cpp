#include "client.h"
#include <chrono>
#include <iostream>
#include <thread>
#include "inbox.h"

Client::Client(std::string name, Inbox<Client>& inbox)
    : name{name}, inbox(inbox) {}

void Client::send(Message& msg) { inbox.recv(msg); }

void Client::recv(Message& msg) {
  // std::cout << name << " rcv msg: " << msg.message << std::endl;

  if (msg.message == "PING") {
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    send(*(new Message{"PONG", name, msg.from}));
  }
}

std::string Client::get_name() { return name; }
