#include "message.h"

Message::Message(std::string message, std::string from, std::string to)
    : message(message), from(from), to(to) {}

bool Message::operator==(Message const& rhs) const {
  return message == rhs.message && from == rhs.from && to == rhs.to;
}
