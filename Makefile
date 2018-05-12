CC=g++
CFLAGS=-std=c++14
COPTS=-pthread
LIBGTEST=-I$(HOME)/Code/googletest/googletest/include $(HOME)/Code/googletest/googletest/build/libgtest.a $(HOME)/Code/googletest/googletest/build/libgtest_main.a

TASTE_DIR=taste
SRC=$(TASTE_DIR)/taste.cpp $(TASTE_DIR)/message.cpp

TEST_DIR=tests
TEST_MAIN=$(TEST_DIR)/main.cpp

all: clsc expectmsg_sleep expectmsg unordered unordered_sleep
	@echo "Done."

clsc:
	clear;clear;

unordered_sleep:
	$(CC) $(CFLAGS) $(COPTS) -g -o unordered_sleep.out $(TEST_MAIN) $(TEST_DIR)/unordered_sleep.cpp $(SRC) $(LIBGTEST) -I$(TASTE_DIR) -I$(TEST_DIR)

unordered:
	$(CC) $(CFLAGS) $(COPTS) -g -o unordered.out $(TEST_MAIN) $(TEST_DIR)/unordered.cpp $(SRC) $(LIBGTEST) -I$(TASTE_DIR) -I$(TEST_DIR)

expectmsg_sleep:
	$(CC) $(CFLAGS) $(COPTS) -g -o expect_msg_sleep.out $(TEST_MAIN) $(TEST_DIR)/expect_msg_sleep.cpp $(SRC) $(LIBGTEST) -I$(TASTE_DIR) -I$(TEST_DIR)

expectmsg:
	$(CC) $(CFLAGS) $(COPTS) -g -o expect_msg.out $(TEST_MAIN) $(TEST_DIR)/expect_msg.cpp $(SRC) $(LIBGTEST) -I$(TASTE_DIR) -I$(TEST_DIR)

clean:
	rm -f *.out
