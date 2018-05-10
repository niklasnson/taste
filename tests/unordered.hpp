#ifndef UNORDERED_H
#define UNORDERED_H

#include <chrono>

/*!
 * \brief A timer class where done() will return true if the timer has "gone
 * off".
 */
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

/*!
 * Returns the next incoming message for a specific receiver.
 */
Message next_message(std::string recipient, std::vector<Message>* log) {
  while (log->empty()) {
    continue;
  }
  while (log->back().to != recipient) {
    continue;
  }
  return log->back();
}

/*!
 * Assert that the next message received by expected.to, is equal to expected.
 */
#define ASSERT_MSG(expected)                                \
  do {                                                      \
    std::vector<Message>* am_log = taste->get_log();        \
    ASSERT_EQ(expected, next_message(expected.to, am_log)); \
  } while (false)

/*!
 * Expect that the next message received by expected.to, is equal to expected.
 */
#define EXPECT_MSG(expected)                                \
  do {                                                      \
    std::vector<Message>* am_log = taste->get_log();        \
    EXPECT_EQ(expected, next_message(expected.to, am_log)); \
  } while (false)

/*!
 * Assert that the next message received by expected.to, is equal to expected.
 * Function also takes a double for a timeout that fails the assertion if
 * exceeded.
 */
#define ASSERT_MSG_TIMER(expected, timeout)                   \
  do {                                                        \
    std::vector<Message>* am_log = taste->get_log();          \
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

/*!
 * Expect that the next message received by expected.to, is equal to expected.
 * Function also takes a double for a timeout that fails the expect if
 * exceeded.
 */
#define EXPECT_MSG_TIMER(expected, timeout)                   \
  do {                                                        \
    std::vector<Message>* am_log = taste->get_log();          \
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

/*!
 * Parameter is a list containing messages to assert in an unordered fashion.
 */
#define ASSERT_UNORDERED(expects_list)                                 \
  do {                                                                 \
    std::vector<Message>* au_log = taste->get_log();                   \
    /*std::mutex* au_log_lock = inbox->get_lock();*/                   \
    while (au_log->empty()) {                                          \
      continue;                                                        \
    }                                                                  \
    bool au_done{false};                                               \
    while (!au_done) {                                                 \
      for (auto it{expects_list.begin()}; it != expects_list.end();) { \
        bool removed{false};                                           \
        /*au_log_lock->lock();*/                                       \
        for (auto& msg : *au_log) {                                    \
          if (msg == *it) {                                            \
            ASSERT_EQ(*it, msg);                                       \
            it = expects_list.erase(it);                               \
            removed = true;                                            \
            break;                                                     \
          }                                                            \
        }                                                              \
        /*au_log_lock->unlock();*/                                     \
        if (!removed) {                                                \
          ++it;                                                        \
        }                                                              \
      }                                                                \
      if (expects_list.empty()) au_done = !au_done;                    \
    }                                                                  \
  } while (false)

/*!
 * Parameter is a list containing messages to expect in an unordered fashion.
 */
#define EXPECT_UNORDERED(expects_list)                                 \
  do {                                                                 \
    std::vector<Message>* au_log = taste->get_log();                   \
    while (au_log->empty()) {                                          \
      continue;                                                        \
    }                                                                  \
    bool au_done{false};                                               \
    while (!au_done) {                                                 \
      for (auto it{expects_list.begin()}; it != expects_list.end();) { \
        bool removed{false};                                           \
        for (auto& msg : *au_log) {                                    \
          if (msg == *it) {                                            \
            EXPECT_EQ(*it, msg);                                       \
            it = expects_list.erase(it);                               \
            removed = true;                                            \
            break;                                                     \
          }                                                            \
        }                                                              \
        if (!removed) {                                                \
          ++it;                                                        \
        }                                                              \
      }                                                                \
      if (expects_list.empty()) au_done = !au_done;                    \
    }                                                                  \
  } while (false)

/*!
 * First parameter is a vector containing messages to assert in an unordered
 * fashion. Second is a double to which starts a timer and fails the assertion
 * if reached.
 */
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

/*!
 * First parameter is a vector containing messages to expect in an unordered
 * fashion. Second is a double to which starts a timer and fails the expect
 * if reached.
 */
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