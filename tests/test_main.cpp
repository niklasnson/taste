#include <gtest/gtest.h>
#include <thread>

void exec_gtest(int argc, char* argv[], int& res) {
  ::testing::InitGoogleTest(&argc, argv);
  res = RUN_ALL_TESTS();
}

int main(int argc, char* argv[]) {
  int res{-1};
  std::thread gt(exec_gtest, argc, argv, std::ref(res));
  gt.join();
  return res;
}
