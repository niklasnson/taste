#include "client.h"
#include <chrono>
#include <iostream>
#include <thread>
#include "inbox.h"

#include <random>

Client::Client(std::string name, Inbox<Client>& inbox)
    : name{name}, inbox(inbox) {}

void Client::send(Message& msg) {
  std::random_device rd;
  std::default_random_engine gen(rd());
  std::uniform_int_distribution<int> dist(0, 1000);
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
