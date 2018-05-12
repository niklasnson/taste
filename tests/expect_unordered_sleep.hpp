#ifndef EXPECT_UNORDERED_SLEEP_HPP
#define EXPECT_UNORDERED_SLEEP_HPP

#define EXPECT_UNORDERED_SLEEP(eus_messages, eus_sleep)               \
do {                                                                  \
  std::this_thread::sleep_for(std::chrono::milliseconds(eus_sleep));  \
  auto eus_log = taste->get_log();                                    \
                                                                      \
  int eus_found{0};                                                   \
  /* Go through the log */                                            \
  for (auto& eus_msg_l : *eus_log) {                                  \
    for (auto& eus_msg_a : *eus_messages) {                           \
      if (eus_msg_l == eus_msg_a) {                                   \
        EXPECT_EQ(eus_msg_l, eus_msg_a);                              \
        ++eus_found;                                                  \
      }                                                               \
    }                                                                 \
  }                                                                   \
  EXPECT_EQ(eus_messages->size(), eus_found);                         \
 } while (false)

#endif /* EXPECT_UNORDERED_SLEEP_HPP */
