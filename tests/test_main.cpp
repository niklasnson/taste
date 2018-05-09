#include <arguments.h>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <thread>

unsigned seed;
unsigned test_sleep;
unsigned n_messages;

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  if (argc < 4) {
    std::cerr << "usage: seed messages sleep_one sleep_uno" << std::endl;
    return -1;
  }
  seed = std::stoull(argv[1], nullptr);
  n_messages = std::stoull(argv[2], nullptr);
  test_sleep = std::stoull(argv[3], nullptr);
  std::cout << "[==========]" << std::endl;
  std::cout << "[  Config  ]       seed: " << seed << std::endl;
  std::cout << "[  Config  ] n_messages: " << n_messages << std::endl;
  std::cout << "[  Config  ]  test_sleep: " << test_sleep << std::endl;
  return RUN_ALL_TESTS();
}
