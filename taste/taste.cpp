#include "taste.hpp"
#include <iostream>
#include <iterator>

Taste::Taste(std::vector<Message> const& messages, unsigned const& seed,
             int const& sleep_max)
    : messages{messages}, inbox{}, gen(seed), dist_sleep(0, sleep_max) {}

void Taste::sleep_random() {
  std::this_thread::sleep_for(std::chrono::milliseconds(dist_sleep(gen)));
}

void Taste::recv_random() {
  std::uniform_int_distribution<int> dist(0, messages.size() - 1);
  auto n = dist(gen);
  auto msg = messages.at(n);
  messages.erase(std::next(messages.begin(), n));
  inbox.push_back(msg);
  std::cout << msg << std::endl;
}

std::vector<Message> Taste::get_log() { return inbox; }

int Taste::run() {
  bool done{false};
  while (!done) {
    if (messages.empty())
      done = true;
    else {
      sleep_random();
      recv_random();
    }
  }
  return 0;
}
