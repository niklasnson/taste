#include <iostream>
#include "client.h"
#include "inbox.h"
#include "message.h"

void usage(char* name) {
  std::cout << std::endl
            << name << " [options]" << std::endl
            << "Options:" << std::endl;
}

int main(int argc, char* argv[]) {
  Inbox<Client> inbox;
  unsigned seed{1337};
  Client alice("Alice", inbox, seed);
  Client bob("Bob", inbox, seed);
  Message message("PING", "Alice", "Bob");
  inbox.enroll(alice);
  inbox.enroll(bob);
  alice.send(message);
  return 0;
}
