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

/*

TEST_F(MessagesUnorderedTest, SleepExpectUnordered) {
  Message msg1{"Mr. Watson--come here--I want to see you.", alice->get_name(),
               bob->get_name()};
  Message msg2{"Merry Christmas.", bob->get_name(), alice->get_name()};
  Message msg3{"QUERTYIOP", alice->get_name(), bob->get_name()};
  Message msg4{"ASDFGHJK", bob->get_name(), alice->get_name()};

  // The messages we're supposed to find.
  std::vector<Message> messages{msg1, msg2, msg3, msg4};

  // Build all packets which should be sent.
  std::vector<Packet> packets{Packet(msg1, alice), Packet(msg2, bob),
                              Packet(msg3, alice), Packet(msg4, bob)};
  for (int i{0}; i < n_messages; i++) {
    Client* sender = get_random_client();
    Message annoying{"[" + std::to_string(i) + "]Are We There Yet?",
                     sender->get_name(), get_random_client()->get_name()};
    packets.push_back(Packet(annoying, sender));
  }

  // Send messages in a random order.
  std::vector<std::thread> threads{};
  auto order = get_order(packets.size());
  for (auto& i : order) {
    std::thread tr(send_message, std::ref(packets.at(i).message),
                   packets.at(i).sender);
    threads.push_back(std::move(tr));
  }

  // Expecting messages unordered with sleep.
  std::this_thread::sleep_for(std::chrono::milliseconds(sleep_uno1));
  auto log = inbox->get_log();

  // Go through the log
  Message test_message{"Didn't find the correct message", ":(", ":("};
  Message found_message = test_message;
  for (auto& msg : *log) {
    if (msg == msg1) {
      found_message = msg1;
      break;
    }
  }
  EXPECT_EQ(msg1, found_message);

  found_message = test_message;
  std::this_thread::sleep_for(std::chrono::milliseconds(sleep_uno2));
  for (auto& msg : *log) {
    if (msg == msg2) {
      found_message = msg2;
    }
  }
  EXPECT_EQ(msg2, found_message);

  found_message = test_message;
  std::this_thread::sleep_for(std::chrono::milliseconds(sleep_uno3));
  for (auto& msg : *log) {
    if (msg == msg3) {
      found_message = msg3;
      break;
    }
  }
  EXPECT_EQ(msg3, found_message);

  found_message = test_message;
  std::this_thread::sleep_for(std::chrono::milliseconds(sleep_uno4));
  for (auto& msg : *log) {
    if (msg == msg4) {
      found_message = msg4;
      break;
    }
  }
  EXPECT_EQ(msg4, found_message);

  for (auto it{threads.begin()}; it != threads.end(); ++it) it->join();
}
*/