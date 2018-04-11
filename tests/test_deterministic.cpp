#include <gtest/gtest.h>

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

TEST_F(PackageTest, SendSome) {
  alice->send(*(new Message{"PING", alice->get_name(), bob->get_name()}));
  ASSERT_MSG(*(new Message{"PONG", bob->get_name(), alice->get_name()}));
}
