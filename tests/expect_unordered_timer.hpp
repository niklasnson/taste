#ifndef EXPECT_UNORDERED_TIMER_HPP
#define EXPECT_UNORDERED_TIMER_HPP

#include "timer.hpp"
/*!
 * First parameter is a vector containing messages to expect in an unordered
 * fashion. Second is a double to which starts a timer and fails the expect
 * if reached.
 */
#define EXPECT_UNORDERED_TIMER(expects_list, timeout_ms)                  \
  do {                                                                    \
    Timer au_timer{timeout_ms};                                           \
    std::vector<Message>* au_log = inbox->get_log();                      \
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
        for (auto& msg : *au_log) {                                       \
          if (msg == *it) {                                               \
            EXPECT_EQ(*it, msg);                                          \
            it = expects_list.erase(it);                                  \
            removed = true;                                               \
            break;                                                        \
          }                                                               \
        }                                                                 \
        if (!removed) {                                                   \
          ++it;                                                           \
        }                                                                 \
      }                                                                   \
      if (expects_list.empty()) au_done = !au_done;                       \
    }                                                                     \
  } while (false)

#endif /* EXPECT_UNORDERED_TIMER_HPP */
