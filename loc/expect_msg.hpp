  do {
    std::vector<Message>* am_log = taste->get_log();
    while (am_log->empty()) {
      continue;
    }
    while (am_log->back().to != expected.to) {
      continue;
    }
    EXPECT_EQ(expected, am_log->back());
  } while (false)
