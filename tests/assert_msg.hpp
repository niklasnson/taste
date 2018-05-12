#ifndef ASSERT_MSG_HPP
#define ASSERT_MSG_HPP

/*!
 * Assert that the next message received by expected.to, is equal to expected.
 */
#define ASSERT_MSG(expected)                                \
  do {                                                      \
    std::vector<Message>* am_log = taste->get_log();        \
    while (log->empty()) {                                  \
      continue;                                             \
    }                                                       \
    while (log->back().to != expected.to) {                 \
      continue;                                             \
    }                                                       \
    ASSERT_EQ(expected, am_log.back());                     \
  } while (false)

#endif /*ASSERT_MSG_HPP*/
