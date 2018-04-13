#ifndef INBOX_STUB_H
#define INBOX_STUB_H

#include <map>
#include <mutex>
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
  std::mutex* get_lock();

 private:
  std::vector<Message> log;
  std::mutex log_lock;
};

template <typename T>
void InboxStub<T>::recv(Message& msg) {
  log_lock.lock();
  log.push_back(msg);
  log_lock.unlock();
  Inbox<T>::recv(msg);
}

template <typename T>
std::mutex* InboxStub<T>::get_lock() {
  return &log_lock;
}

template <typename T>
std::vector<Message>* InboxStub<T>::get_log() {
  return &log;
}
#endif
