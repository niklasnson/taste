#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <thread>

#include "../taste/client.h"
#include "../taste/message.h"
#include "stubs/inbox_stub.h"
#include "unordered.h"

struct PackageTest : testing::Test {
  InboxStub<Client>* inbox;
  Client* alice;
  Client* bob;

  PackageTest() {
    inbox = new InboxStub<Client>{};
    alice = new Client("Alice", *dynamic_cast<Inbox<Client>*>(inbox));
    bob = new Client("Bob", *dynamic_cast<Inbox<Client>*>(inbox));

    inbox->enroll(*alice);
    inbox->enroll(*bob);
  }
  virtual ~PackageTest() {
    delete alice;
    delete bob;
    delete inbox;
  }
};

/*!
 * Helper function for sending one message
 */
void send_message(Message& msg, Client* sender) { sender->send(msg); }

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
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  auto log = inbox->get_log();
  EXPECT_EQ(response, log->back());

  msg_thread.join();
}

struct MessagesUnorderedTest : testing::Test {
  InboxStub<Client>* inbox;
  Client* alice;
  Client* bob;
  std::vector<Client*> clients;

  std::default_random_engine gen;
  std::uniform_int_distribution<int> dist;

  MessagesUnorderedTest() {
    inbox = new InboxStub<Client>{};
    alice = new Client("Alice", *dynamic_cast<Inbox<Client>*>(inbox));
    bob = new Client("Bob", *dynamic_cast<Inbox<Client>*>(inbox));

    clients.push_back(alice);
    clients.push_back(bob);
    clients.push_back(
        new Client("Chuck", *dynamic_cast<Inbox<Client>*>(inbox)));
    clients.push_back(
        new Client("Mallory", *dynamic_cast<Inbox<Client>*>(inbox)));
    clients.push_back(
        new Client("Oscar", *dynamic_cast<Inbox<Client>*>(inbox)));

    for (auto client : clients) inbox->enroll(*client);

    dist = *(new std::uniform_int_distribution<int>(0, clients.size() - 1));
  }

  Client* get_random_client() { return clients.at(dist(gen)); }

  std::thread send_message_randomly(Message& msg) {
    Client* sender = get_random_client();
    msg.from = sender->get_name();
    msg.to = get_random_client()->get_name();
    return std::thread(send_message, std::ref(msg), sender);
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
  std::vector<Message> messages{msg1, msg2, msg3, msg4};

  std::thread msg_thread1(send_message, std::ref(msg1), alice);
  std::thread msg_thread2(send_message, std::ref(msg2), bob);
  std::thread msg_thread3(send_message, std::ref(msg3), alice);
  std::thread msg_thread4(send_message, std::ref(msg4), bob);
  EXPECT_UNORDERED(messages);
  msg_thread1.join();
  msg_thread2.join();
  msg_thread3.join();
  msg_thread4.join();
}

TEST_F(MessagesUnorderedTest, SleepExpectUnordered) {
  Message msg1{"Mr. Watson--come here--I want to see you.", alice->get_name(),
               bob->get_name()};
  Message msg2{"Merry Christmas.", bob->get_name(), alice->get_name()};
  Message msg3{"QUERTYIOP", alice->get_name(), bob->get_name()};
  Message msg4{"ASDFGHJK", bob->get_name(), alice->get_name()};
  std::vector<Message> messages{msg1, msg2, msg3, msg4};
  std::vector<std::thread> threads{};

  std::vector<Message> send_messages{msg1, msg2, msg3, msg4};
  for (int i{0}; i < 100; i++) {
    Client* sender = get_random_client();
    Message annoying{"[" + std::to_string(i) + "]Are We There Yet?",
                     sender->get_name(), get_random_client()->get_name()};
    send_messages.push_back(annoying);

    std::thread tr(send_message, std::ref(annoying), sender);
    threads.push_back(std::move(tr));
  }

  std::thread msg_thread1(send_message, std::ref(msg1), alice);
  std::thread msg_thread2(send_message, std::ref(msg2), bob);
  std::thread msg_thread3(send_message, std::ref(msg3), alice);
  std::thread msg_thread4(send_message, std::ref(msg4), bob);
  /*
   * Expecting things unordered with sleep
   */
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  auto log = inbox->get_log();

  std::string test{""};
  for (auto& msg : *log) {
    if (msg == msg1) {
      EXPECT_EQ(msg, msg1);
      test = "test1";
    }
  }
  EXPECT_EQ("test1", test);

  test = "";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  for (auto& msg : *log) {
    if (msg == msg2) {
      EXPECT_EQ(msg, msg2);
      test = "test2";
    }
  }
  EXPECT_EQ("test2", test);

  test = "";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  for (auto& msg : *log) {
    if (msg == msg3) {
      EXPECT_EQ(msg, msg3);
      test = "test3";
    }
  }
  EXPECT_EQ("test3", test);

  test = "";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  for (auto& msg : *log) {
    if (msg == msg4) {
      EXPECT_EQ(msg, msg4);
      test = "test4";
    }
  }
  EXPECT_EQ("test4", test);

  threads.push_back(std::move(msg_thread1));
  threads.push_back(std::move(msg_thread2));
  threads.push_back(std::move(msg_thread3));
  threads.push_back(std::move(msg_thread4));
  for (auto it{threads.begin()}; it != threads.end(); ++it) it->join();
}
