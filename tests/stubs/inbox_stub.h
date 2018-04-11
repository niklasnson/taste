#ifndef INBOX_STUB_H
#define INBOX_STUB_H

#include <map>
#include <string>
#include <vector>
#include "../../taste/inbox.h"
#include "../../taste/message.h"

template <typename T>
class InboxStub : public Inbox<T> {
 public:
  InboxStub() = default;
  void recv(Message& msg) override;
  std::vector<Message>* get_log();

 private:
  std::vector<Message> log;
};

template <typename T>
void InboxStub<T>::recv(Message& msg) {
  log.push_back(msg);
  Inbox<T>::recv(msg);
}

template <typename T>
std::vector<Message>* InboxStub<T>::get_log() {
  return &log;
}
#endif
