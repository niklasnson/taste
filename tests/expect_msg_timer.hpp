#ifndef EXPECT_MSG_TIMER_HPP
#define EXPECT_MSG_TIMER_HPP

#include "timer.hpp"
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

#endif /* EXPECT_MSG_TIMER_HPP */
