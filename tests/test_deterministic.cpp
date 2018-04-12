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
void send_message(Client* alice, Client* bob) {
  alice->send(*(new Message{"PING", alice->get_name(), bob->get_name()}));
}

TEST_F(PackageTest, SendSome) {
  std::thread msg_thread(send_message, alice, bob);
  Message msg{"PONG", bob->get_name(), alice->get_name()};
  ASSERT_MSG(msg);
  msg_thread.join();
}

TEST(Whatever, WaitingForTheSun) { ASSERT_EQ(true, true); }
