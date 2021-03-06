#ifndef TASTE_H
#define TASTE_H

#include <chrono>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include "message.hpp"

class Taste {
 public:
  Taste(std::vector<Message> const& messages, unsigned const& seed,
        int const& sleep_max);
  void sleep_random();
  void recv_random();
  int run();
  std::vector<Message>* get_log();

 private:
  std::vector<Message> messages;
  std::vector<Message> inbox;
  std::uniform_int_distribution<int> dist_sleep;
  std::mt19937 gen;
};
#endif /* TASTE_H */
