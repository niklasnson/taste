
// TEST_F(PackageTest, SendOneMessageWithTimeout) {
//   std::thread msg_thread(
//       send_message,
//       std::ref(*(new Message{"PING", alice->get_name(), bob->get_name()})),
//       alice);
//   Message msg{"PONG", bob->get_name(), alice->get_name()};
//   EXPECT_MSG_TIMER(msg, 1.5);
//   msg_thread.join();
// }

// TEST_F(PackageTest, AssertUnorderedWithTimer) {
//   Message tjena{"Tjena.", alice->get_name(), bob->get_name()};
//   Message tja{"Tja.", bob->get_name(), alice->get_name()};
//   Message leget{"Läget?", alice->get_name(), bob->get_name()};
//   std::vector<Message> messages{tja, leget, tjena};
//   std::vector<std::thread> threads{};

//   for (int i{0}; i < 100; i++) {
//     Message annoying{"[" + std::to_string(i) + "]Are We There Yet?",
//                      bob->get_name(), alice->get_name()};
//     std::thread msg_thread(send_message, std::ref(annoying), bob);
//     threads.push_back(std::move(msg_thread));
//   }
//   EXPECT_UNORDERED_TIMER(messages, 0.0);

//   std::thread msg_thread1(send_message, std::ref(tjena), alice);
//   std::thread msg_thread2(send_message, std::ref(tja), alice);
//   std::thread msg_thread3(send_message, std::ref(leget), alice);
//   threads.push_back(std::move(msg_thread1));
//   threads.push_back(std::move(msg_thread2));
//   threads.push_back(std::move(msg_thread3));
//   for (auto it{threads.begin()}; it != threads.end(); ++it) it->join();
// }