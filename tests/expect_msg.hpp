#ifndef EXPECT_MSG_HPP
#define EXPECT_MSG_HPP

/*!
 * EXPECT that the next message received or sent by expected.to, is equal to expected.
 */
#define EXPECT_MSG(expected)                                \
  do {                                                      \
    std::vector<Message>* am_log = taste->get_log();        \
    while (am_log->empty()) {                               \
      continue;                                             \
    }                                                       \
    while (am_log->back().to != expected.to) {              \
      continue;                                             \
    }                                                       \
    EXPECT_EQ(expected, am_log->back());                    \
  } while (false)

#endif /*EXPECT_MSG_HPP*/
