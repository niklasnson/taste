#ifndef EXPECT_MSG_SLEEP_HPP
#define EXPECT_MSG_SLEEP_HPP

#define EXPECT_MSG_SLEEP(ems_message, ems_sleep)                        \
  do {                                                                  \
    std::this_thread::sleep_for(std::chrono::milliseconds(ems_sleep));  \
    auto ems_log = taste->get_log();                                    \
    EXPECT_EQ(ems_message, (log->empty() ? *fail : ems_log->back()));   \
  } while (false)

#endif /* EXPECT_MSG_SLEEP_HPP */
