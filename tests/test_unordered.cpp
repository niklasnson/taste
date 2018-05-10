#include <gtest/gtest.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <thread>

#include "../taste/message.hpp"
#include "../taste/taste.hpp"
#include "arguments.h"
#include "unordered.h"

struct PackageTest : testing::Test {
  Taste* taste;
  Message* fail;
  std::string const alice{"Alice"};
  std::string const bob{"Bob"};

  std::vector<Message>* messages;

  PackageTest() {
    fail = new Message{"Fail", "Fail", "Fail"};
    Message msg1{"Mr. Watson--come here--I want to see you.", alice, bob};
    Message msg2{"Merry Christmas.", bob, alice};
    Message msg3{"QUERTYIOP", alice, bob};
    Message msg4{"ASDFGHJK", bob, alice};

    messages = new std::vector<Message>{msg1, msg2, msg3, msg4};
    std::vector<Message> more_messages{*messages};

    for (int i{0}; i < n_messages; ++i) {
      Message msg{"[ Message " + std::to_string(i) + " ]", ":)", ":("};
      more_messages.push_back(msg);
    }

    taste = new Taste{more_messages, seed, 1000};
  }

  virtual ~PackageTest() {
    delete taste;
    delete fail;
    delete messages;
  }
};

TEST_F(PackageTest, ExpectUnordered) {
  std::thread t{&Taste::run, taste};
  t.detach();

  EXPECT_UNORDERED((*messages));
}
