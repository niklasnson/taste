#include <gtest/gtest.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <thread>

#include "../taste/client.h"
#include "../taste/message.h"
#include "arguments.h"
#include "stubs/inbox_stub.h"
#include "unordered.h"

/*!
 * Helper function for sending one message
 */
void send_message(Message& msg, Client* sender) { sender->send(msg); }
struct PackageTest : testing::Test {
  InboxStub<Client>* inbox;
  Client* alice;
  Client* bob;

  PackageTest() {
    inbox = new InboxStub<Client>{};
    alice = new Client("Alice", *dynamic_cast<Inbox<Client>*>(inbox), seed);
    bob = new Client("Bob", *dynamic_cast<Inbox<Client>*>(inbox), seed);

    inbox->enroll(*alice);
    inbox->enroll(*bob);
    Message msg{"There's always messages in the banana stand.",
                alice->get_name(), bob->get_name()};
    inbox->get_log()->push_back(msg);
  }

  virtual ~PackageTest() {
    delete alice;
    delete bob;
    delete inbox;
  }
};

TEST_F(PackageTest, SendOneMessage) {
  // Send one message
  Message msg{"PING", alice->get_name(), bob->get_name()};
  std::thread msg_thread(send_message, std::ref(msg), alice);

  // Block until this message arrives.
  Message response{"PONG", bob->get_name(), alice->get_name()};
  EXPECT_MSG(response);
  msg_thread.join();
}

TEST_F(PackageTest, SleepExpectMsg) {
  // Send one message
  Message msg{"PING", alice->get_name(), bob->get_name()};
  std::thread msg_thread(send_message, std::ref(msg), alice);

  // Use sleep to expect correct answer
  Message response{"PONG", bob->get_name(), alice->get_name()};
  std::this_thread::sleep_for(std::chrono::milliseconds(sleep_one));
  auto log = inbox->get_log();
  EXPECT_EQ(response, log->back());

  msg_thread.join();
}

struct Packet {
  Packet(Message& message, Client* sender) : message{message}, sender{sender} {}
  Message& message;
  Client* sender;
};

struct MessagesUnorderedTest : testing::Test {
  InboxStub<Client>* inbox;
  Client* alice;
  Client* bob;
  std::vector<Client*> clients;

  std::mt19937 gen;
  std::uniform_int_distribution<int> dist;

  MessagesUnorderedTest() {
    inbox = new InboxStub<Client>{};
    alice = new Client("Alice", *dynamic_cast<Inbox<Client>*>(inbox), seed);
    bob = new Client("Bob", *dynamic_cast<Inbox<Client>*>(inbox), seed);

    clients.push_back(alice);
    clients.push_back(bob);
    clients.push_back(
        new Client("Chuck", *dynamic_cast<Inbox<Client>*>(inbox), seed));
    clients.push_back(
        new Client("Mallory", *dynamic_cast<Inbox<Client>*>(inbox), seed));
    clients.push_back(
        new Client("Oscar", *dynamic_cast<Inbox<Client>*>(inbox), seed));

    for (auto client : clients) inbox->enroll(*client);

    gen.seed(seed);
    dist = *(new std::uniform_int_distribution<int>(0, clients.size() - 1));

    Message msg{"There's always messages in the banana stand.",
                alice->get_name(), bob->get_name()};
    inbox->get_log()->push_back(msg);
  }

  Client* get_random_client() { return clients.at(dist(gen)); }

  std::thread send_message_randomly(Message& msg) {
    Client* sender = get_random_client();
    msg.from = sender->get_name();
    msg.to = get_random_client()->get_name();
    return std::thread(send_message, std::ref(msg), sender);
  }

  std::vector<int>& get_order(int size) {
    std::vector<int>* v = new std::vector<int>(size);
    std::generate(v->begin(), v->end(), [n = 0]() mutable { return n++; });
    std::shuffle(v->begin(), v->end(), gen);
    return *v;
  }

  virtual ~MessagesUnorderedTest() {
    for (auto client : clients) delete client;
    delete inbox;
  }
};

TEST_F(MessagesUnorderedTest, ExpectUnordered) {
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

  EXPECT_UNORDERED(messages);
  for (auto it{threads.begin()}; it != threads.end(); ++it) it->join();
}

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
