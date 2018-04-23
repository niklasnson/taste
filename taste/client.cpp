#include "client.h"
#include <chrono>
#include <iostream>
#include <thread>
#include "inbox.h"

#include <random>

Client::Client(std::string name, Inbox<Client>& inbox, unsigned seed)
    : name{name}, inbox(inbox), gen(seed), dist(0, 1000) {}

void Client::send(Message& msg) {
  std::this_thread::sleep_for(std::chrono::milliseconds(dist(gen)));
  inbox.recv(msg);
}

void Client::recv(Message& msg) {
  if (msg.message == "PING") {
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    send(*(new Message{"PONG", name, msg.from}));
  }
}

std::string Client::get_name() { return name; }
