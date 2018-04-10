#ifndef INBOX_H 
#define INBOX_H 

#include "message.h"
#include <map>

template <typename T> 
class Inbox {
  public: 
    Inbox();
    void enroll(T & client);
    void recv(Message & msg);
  private:
    std::map<std::string, T*> routing_table;  
};
#include "inbox.impl"
#endif
