#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

class Message {
  public: 
    Message(std::string message, std::string from, std::string to);
    std::string message;
    std::string from;
    std::string to;
};

#endif
