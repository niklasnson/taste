#include <gtest/gtest.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <thread>

#include "../taste/message.h"
#include "../taste/taste.hpp"
#include "arguments.h"
#include "unordered.h"

struct PackageTest : testing::Test {
  Taste* taste;
  Message* fail;
  PackageTest() {
    fail = new Message{"Fail", "Fail", "Fail"};
    std::vector<Message> messages{Message("PING", "Alice", "Bob"),
                                  Message("PONG", "Bob", "Alice")};
    taste = new Taste{messages, seed, 1000};
  }

  virtual ~PackageTest() {
    delete taste;
    delete fail;
  }
};

TEST_F(PackageTest, SleepExpectMsg) {
  std::thread t{&Taste::run, taste};
  t.detach();
  // Use sleep to expect correct message
  Message response{"PONG", "Bob", "Alice"};
  std::this_thread::sleep_for(std::chrono::milliseconds(sleep_one));
  auto log = taste->get_log();

  EXPECT_EQ(response, (log->empty() ? *fail : log->back()));
}