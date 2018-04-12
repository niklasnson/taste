#ifndef UNORDERED_H
#define UNORDERED_H

#include <chrono>

std::ostream& operator<<(std::ostream& os, Message const& m) {
  return os << "<" << m.message << " " << m.from << " " << m.to << ">";
}

class Timer {
 public:
  Timer(double max_seconds)
      : start{std::chrono::high_resolution_clock::now()}, max{max_seconds} {}

  std::chrono::high_resolution_clock::time_point start;
  double max;

  bool done() {
    using namespace std::chrono;
    high_resolution_clock::time_point now = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(now - start);
    return time_span.count() >= max;
  }
};

#define ASSERT_MSG(expected)                         \
  do {                                               \
    std::vector<Message>* am_log = inbox->get_log(); \
    while (am_log->empty()) {                        \
      continue;                                      \
    }                                                \
    while (am_log->back().to != expected.to) {       \
      continue;                                      \
    }                                                \
    ASSERT_EQ(expected, am_log->back());             \
  } while (false)

#define ASSERT_MSG_TIMER(expected, timeout)                                \
  do {                                                                     \
    std::vector<Message>* am_log = inbox->get_log();                       \
    Timer timer{timeout};                                                  \
    while (am_log->empty()) {                                              \
      continue;                                                            \
    }                                                                      \
    while (am_log->back().to != expected.to) {                             \
      if (timer.done()) {                                                  \
        ASSERT_TRUE(false) << "ASSERT_MSG(" << expected << ") timed out."; \
      } else {                                                             \
        continue;                                                          \
      }                                                                    \
    }                                                                      \
    ASSERT_EQ(expected, am_log->back());                                   \
  } while (false)

#endif /* UNORDERED_H */