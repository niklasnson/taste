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

Message& next_message(std::string recipient, std::vector<Message>* log) {
  while (log->empty()) {
    continue;
  }
  while (log->back().to != recipient) {
    continue;
  }
  return log->back();
}

#define ASSERT_MSG(expected)                                \
  do {                                                      \
    std::vector<Message>* am_log = inbox->get_log();        \
    ASSERT_EQ(expected, next_message(expected.to, am_log)); \
  } while (false)

#define EXPECT_MSG(expected)                                \
  do {                                                      \
    std::vector<Message>* am_log = inbox->get_log();        \
    EXPECT_EQ(expected, next_message(expected.to, am_log)); \
  } while (false)

#define ASSERT_MSG_TIMER(expected, timeout)                   \
  do {                                                        \
    std::vector<Message>* am_log = inbox->get_log();          \
    Timer timer{timeout};                                     \
    while (am_log->empty()) {                                 \
      continue;                                               \
    }                                                         \
    while (am_log->back().to != expected.to) {                \
      if (timer.done()) {                                     \
        ASSERT_TRUE(false) << "ASSERT_MSG_TIMER(" << expected \
                           << ") timed out.";                 \
        break;                                                \
      } else {                                                \
        continue;                                             \
      }                                                       \
    }                                                         \
    ASSERT_EQ(expected, am_log->back());                      \
  } while (false)

#define EXPECT_MSG_TIMER(expected, timeout)                   \
  do {                                                        \
    std::vector<Message>* am_log = inbox->get_log();          \
    Timer timer{timeout};                                     \
    while (am_log->empty()) {                                 \
      continue;                                               \
    }                                                         \
    while (am_log->back().to != expected.to) {                \
      if (timer.done()) {                                     \
        EXPECT_TRUE(false) << "EXPECT_MSG_TIMER(" << expected \
                           << ") timed out.";                 \
        break;                                                \
      } else {                                                \
        continue;                                             \
      }                                                       \
    }                                                         \
    EXPECT_EQ(expected, am_log->back());                      \
  } while (false)

#define ASSERT_UNORDERED(expects_list)                                 \
  do {                                                                 \
    std::vector<Message>* au_log = inbox->get_log();                   \
    std::mutex* au_log_lock = inbox->get_lock();                       \
    while (au_log->empty()) {                                          \
      continue;                                                        \
    }                                                                  \
    bool au_done{false};                                               \
    while (!au_done) {                                                 \
      for (auto it{expects_list.begin()}; it != expects_list.end();) { \
        bool removed{false};                                           \
        au_log_lock->lock();                                           \
        for (auto& msg : *au_log) {                                    \
          if (msg == *it) {                                            \
            ASSERT_EQ(*it, msg);                                       \
            it = expects_list.erase(it);                               \
            removed = true;                                            \
            break;                                                     \
          }                                                            \
        }                                                              \
        au_log_lock->unlock();                                         \
        if (!removed) {                                                \
          ++it;                                                        \
        }                                                              \
      }                                                                \
      if (expects_list.empty()) au_done = !au_done;                    \
    }                                                                  \
  } while (false)

#define ASSERT_UNORDERED_TIMER(expects_list, timeout_ms)                  \
  do {                                                                    \
    Timer au_timer{timeout_ms};                                           \
    std::vector<Message>* au_log = inbox->get_log();                      \
    std::mutex* au_log_lock = inbox->get_lock();                          \
    while (au_log->empty()) {                                             \
      continue;                                                           \
    }                                                                     \
    bool au_done{false};                                                  \
    while (!au_done) {                                                    \
      if (au_timer.done()) {                                              \
        std::string expects_left{""};                                     \
        for (auto& e : expects_list) expects_left += e.to_string() + " "; \
        ASSERT_TRUE(false) << "ASSERT_UNORDERED() timed out."             \
                           << "\nMessages left: " << expects_left;        \
        break;                                                            \
      }                                                                   \
      for (auto it{expects_list.begin()}; it != expects_list.end();) {    \
        bool removed{false};                                              \
        au_log_lock->lock();                                              \
        for (auto& msg : *au_log) {                                       \
          if (msg == *it) {                                               \
            ASSERT_EQ(*it, msg);                                          \
            it = expects_list.erase(it);                                  \
            removed = true;                                               \
            break;                                                        \
          }                                                               \
        }                                                                 \
        au_log_lock->unlock();                                            \
        if (!removed) {                                                   \
          ++it;                                                           \
        }                                                                 \
      }                                                                   \
      au_log_lock->unlock();                                              \
      if (expects_list.empty()) au_done = !au_done;                       \
    }                                                                     \
  } while (false)

#define EXPECT_UNORDERED_TIMER(expects_list, timeout_ms)                  \
  do {                                                                    \
    Timer au_timer{timeout_ms};                                           \
    std::vector<Message>* au_log = inbox->get_log();                      \
    std::mutex* au_log_lock = inbox->get_lock();                          \
    while (au_log->empty()) {                                             \
      continue;                                                           \
    }                                                                     \
    bool au_done{false};                                                  \
    while (!au_done) {                                                    \
      if (au_timer.done()) {                                              \
        std::string expects_left{""};                                     \
        for (auto& e : expects_list) expects_left += e.to_string() + " "; \
        EXPECT_TRUE(false) << "ASSERT_UNORDERED() timed out."             \
                           << "\nMessages left: " << expects_left;        \
        break;                                                            \
      }                                                                   \
      for (auto it{expects_list.begin()}; it != expects_list.end();) {    \
        bool removed{false};                                              \
        au_log_lock->lock();                                              \
        for (auto& msg : *au_log) {                                       \
          if (msg == *it) {                                               \
            EXPECT_EQ(*it, msg);                                          \
            it = expects_list.erase(it);                                  \
            removed = true;                                               \
            break;                                                        \
          }                                                               \
        }                                                                 \
        au_log_lock->unlock();                                            \
        if (!removed) {                                                   \
          ++it;                                                           \
        }                                                                 \
      }                                                                   \
      au_log_lock->unlock();                                              \
      if (expects_list.empty()) au_done = !au_done;                       \
    }                                                                     \
  } while (false)

#endif /* UNORDERED_H */