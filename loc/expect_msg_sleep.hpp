  do {
    std::this_thread::sleep_for(std::chrono::milliseconds(ems_sleep));
    auto ems_log = taste->get_log();
    EXPECT_EQ(ems_message, (log->empty() ? *fail : ems_log->back()));
  } while (false)
