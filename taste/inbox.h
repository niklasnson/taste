#ifndef INBOX_H
#define INBOX_H

#include <map>
#include "message.h"

template <typename T>
class Inbox {
 public:
  Inbox();
  void enroll(T& recipient);
  virtual void recv(Message& msg);

 private:
  std::map<std::string, T*> routing_table;
};
#include "inbox.impl"
#endif
