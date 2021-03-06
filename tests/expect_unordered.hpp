#ifndef EXPECT_UNORDERED_HPP
#define EXPECT_UNORDERED_HPP

/*!
 * Parameter is a list containing messages to EXPECT in an unordered fashion.
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

#endif /*EXPECT_UNORDERED_HPP*/
