#include <gtest/gtest.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <thread>

#include "../taste/message.hpp"
#include "../taste/taste.hpp"
#include "arguments.h"
#include "unordered.hpp"

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

  // Block until this message arrives.
  Message response{"PONG", "Bob", "Alice"};
  EXPECT_MSG(response);
}
