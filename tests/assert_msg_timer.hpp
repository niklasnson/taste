#ifndef ASSERT_MSG_TIMER_HPP
#define ASSERT_MSG_TIMER_HPP

#include "timer.hpp"
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

#endif /* ASSERT_MSG_TIMER_HPP */
