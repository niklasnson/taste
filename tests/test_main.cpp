#include <gtest/gtest.h>
#include <seed.h>
#include <string>
#include <thread>

unsigned seed;

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  seed = std::stoull(argv[1], nullptr);
  return RUN_ALL_TESTS();
}
