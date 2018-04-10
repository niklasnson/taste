#include <iostream> 
#include "client.h"
#include "inbox.h"
#include "message.h"

void usage(char* name) {
  std::cout << std::endl << name << " [options]" << std::endl << 
  "Options:" << std::endl;
}

int main(int argc, char *argv[]) {

  Inbox<Client> inbox; 
  Client alice("Alice", inbox); 
  Client bob("Bob", inbox); 
  Message message("PING", "Alice", "Bob");
  inbox.enroll(alice);
  inbox.enroll(bob);
  alice.send(message);
  return 0; 
}
