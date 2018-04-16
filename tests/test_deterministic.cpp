#include <gtest/gtest.h>
#include <iostream>
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

TEST_F(PackageTest, Creation) {
  ASSERT_TRUE(inbox != nullptr);
  ASSERT_TRUE(alice != nullptr);
}

void send_message(Message& msg, Client* sender) { sender->send(msg); }

TEST_F(PackageTest, SendOneMessage) {
  std::thread msg_thread(
      send_message,
      std::ref(*(new Message{"PING", alice->get_name(), bob->get_name()})),
      alice);
  Message msg{"PONG", bob->get_name(), alice->get_name()};
  ASSERT_MSG(msg);
  msg_thread.join();
}

// TEST_F(PackageTest, SendOneMessageWithTimeout) {
//   std::thread msg_thread(
//       send_message,
//       std::ref(*(new Message{"PING", alice->get_name(), bob->get_name()})),
//       alice);
//   Message msg{"PONG", bob->get_name(), alice->get_name()};
//   EXPECT_MSG_TIMER(msg, 1.5);
//   msg_thread.join();
// }

TEST_F(PackageTest, AssertUnordered) {
  Message tjena{"Tjena.", alice->get_name(), bob->get_name()};
  Message tja{"Tja.", bob->get_name(), alice->get_name()};
  Message leget{"Läget?", alice->get_name(), bob->get_name()};
  std::thread msg_thread1(send_message, std::ref(tjena), alice);
  std::thread msg_thread2(send_message, std::ref(tja), alice);
  std::thread msg_thread3(send_message, std::ref(leget), alice);
  std::vector<Message> messages{tja, leget, tjena};
  ASSERT_UNORDERED(messages);
  msg_thread1.join();
  msg_thread2.join();
  msg_thread3.join();
}

// TEST_F(PackageTest, AssertUnorderedWithTimer) {
//   Message tjena{"Tjena.", alice->get_name(), bob->get_name()};
//   Message tja{"Tja.", bob->get_name(), alice->get_name()};
//   Message leget{"Läget?", alice->get_name(), bob->get_name()};
//   std::vector<Message> messages{tja, leget, tjena};
//   std::vector<std::thread> threads{};

//   for (int i{0}; i < 100; i++) {
//     Message annoying{"[" + std::to_string(i) + "]Are We There Yet?",
//                      bob->get_name(), alice->get_name()};
//     std::thread msg_thread(send_message, std::ref(annoying), bob);
//     threads.push_back(std::move(msg_thread));
//   }
//   EXPECT_UNORDERED_TIMER(messages, 0.0);

//   std::thread msg_thread1(send_message, std::ref(tjena), alice);
//   std::thread msg_thread2(send_message, std::ref(tja), alice);
//   std::thread msg_thread3(send_message, std::ref(leget), alice);
//   threads.push_back(std::move(msg_thread1));
//   threads.push_back(std::move(msg_thread2));
//   threads.push_back(std::move(msg_thread3));
//   for (auto it{threads.begin()}; it != threads.end(); ++it) it->join();
// }

TEST_F(PackageTest, SleepAssertMsg) {
  std::thread msg_thread(
      send_message,
      std::ref(*(new Message{"PING", alice->get_name(), bob->get_name()})),
      alice);
  Message msg{"PONG", bob->get_name(), alice->get_name()};

  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  auto log = inbox->get_log();
  ASSERT_EQ(msg, log->back());

  msg_thread.join();
}

TEST_F(PackageTest, SleepAssertUnordered) {
  Message tjena{"Tjena.", alice->get_name(), bob->get_name()};
  Message tja{"Tja.", bob->get_name(), alice->get_name()};
  Message leget{"Läget?", alice->get_name(), bob->get_name()};
  std::vector<Message> messages{tja, leget, tjena};
  std::vector<std::thread> threads{};

  for (int i{0}; i < 100; i++) {
    Message annoying{"[" + std::to_string(i) + "]Are We There Yet?",
                     bob->get_name(), alice->get_name()};
    std::thread msg_thread(send_message, std::ref(annoying), bob);
    threads.push_back(std::move(msg_thread));
  }

  std::thread msg_thread1(send_message, std::ref(tjena), alice);
  std::thread msg_thread2(send_message, std::ref(tja), alice);
  std::thread msg_thread3(send_message, std::ref(leget), alice);
  /*
   * Expecting things unordered with sleep
   */
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  auto log = inbox->get_log();

  bool test{false};
  for (auto& msg : *log) {
    if (msg == tjena) {
      ASSERT_EQ(msg, tjena);
      test = !test;
    }
  }
  ASSERT_TRUE(test);

  test = !test;
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  for (auto& msg : *log) {
    if (msg == tja) {
      ASSERT_EQ(msg, tja);
      test = !test;
    }
  }
  ASSERT_TRUE(test);

  test = !test;
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  for (auto& msg : *log) {
    if (msg == leget) {
      ASSERT_EQ(msg, leget);
      test = !test;
    }
  }
  ASSERT_TRUE(test);

  threads.push_back(std::move(msg_thread1));
  threads.push_back(std::move(msg_thread2));
  threads.push_back(std::move(msg_thread3));
  for (auto it{threads.begin()}; it != threads.end(); ++it) it->join();
}
