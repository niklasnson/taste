#include "message.h"
#include <iostream>

Message::Message(std::string message, std::string from, std::string to)
    : message(message), from(from), to(to) {}

bool Message::operator==(Message const& rhs) const {
  return message == rhs.message && from == rhs.from && to == rhs.to;
}

std::string Message::to_string() const {
  return "<" + message + " " + from + " " + to + ">";
}

std::ostream& operator<<(std::ostream& os, Message const& msg) {
  os << "<" << msg.message << " " << msg.from << " " << msg.to << ">";
  return os;
}