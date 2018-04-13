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

TEST_F(PackageTest, AssertUnordered) {
  Message tjena{"Tjena.", alice->get_name(), bob->get_name()};
  std::thread msg_thread1(send_message, std::ref(tjena), alice);
  Message tja{"Tja.", bob->get_name(), alice->get_name()};
  Message leget{"Läget?", alice->get_name(), bob->get_name()};
  std::thread msg_thread2(send_message, std::ref(tja), alice);
  std::thread msg_thread3(send_message, std::ref(leget), alice);
  std::vector<Message> messages{tja, leget, tjena};
  ASSERT_UNORDERED(messages);
  msg_thread1.join();
  msg_thread2.join();
  msg_thread3.join();
}

TEST(Whatever, WaitingForTheSun) { ASSERT_EQ(true, true); }
