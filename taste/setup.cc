#include <iostream>
#include "client.h"
#include "inbox.h"
#include "message.h"

/*
 * \brief Sets up a test environment and returns the common inbox.
 */
Inbox<Client>* set_up(std::vector<std::string> const& clients, unsigned const& seed) {
  Inbox<Client>* inbox = new Inbox<Client>();
  for (std::string const& name : clients) {
    auto c = new Client(name, *inbox, seed);
    inbox->enroll(*c);
  }
  return inbox;
}
