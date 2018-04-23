#include <arguments.h>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <thread>

unsigned seed;
unsigned sleep_one;
unsigned n_messages;
unsigned sleep_uno1;
unsigned sleep_uno2;
unsigned sleep_uno3;
unsigned sleep_uno4;
int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  seed = std::stoull(argv[1], nullptr);
  sleep_one = std::stoull(argv[2], nullptr);
  n_messages = std::stoull(argv[3], nullptr);
  sleep_uno1 = std::stoull(argv[4], nullptr);
  sleep_uno2 = std::stoull(argv[5], nullptr);
  sleep_uno3 = std::stoull(argv[6], nullptr);
  sleep_uno4 = std::stoull(argv[7], nullptr);
  std::cout << "[==========]" << std::endl;
  std::cout << "[  Config  ]       seed: " << seed << std::endl;
  std::cout << "[  Config  ]  sleep_one: " << sleep_one << std::endl;
  std::cout << "[  Config  ] n_messages: " << n_messages << std::endl;
  std::cout << "[  Config  ] sleep_uno1: " << sleep_uno1 << std::endl;
  std::cout << "[  Config  ] sleep_uno2: " << sleep_uno2 << std::endl;
  std::cout << "[  Config  ] sleep_uno3: " << sleep_uno3 << std::endl;
  std::cout << "[  Config  ] sleep_uno4: " << sleep_uno4 << std::endl;
  return RUN_ALL_TESTS();
}
