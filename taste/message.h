#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

class Message {
 public:
  Message(std::string message, std::string from, std::string to);
  std::string message;
  std::string from;
  std::string to;
  bool operator==(Message const& rhs) const;
  std::string to_string() const;
};

#endif
