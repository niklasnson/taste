CC=g++
CFLAGS=-std=c++14
COPTS=-pthread
LIBGTEST=-I$(HOME)/Code/googletest/googletest/include $(HOME)/Code/googletest/googletest/build/libgtest.a $(HOME)/Code/googletest/googletest/build/libgtest_main.a

TASTE_DIR=taste
SRC=$(TASTE_DIR)/taste.cpp $(TASTE_DIR)/message.cpp

TEST_DIR=tests
TEST_MAIN=$(TEST_DIR)/test_main.cpp

all: clsc test_expectmsg_sleep test_expectmsg test_unordered

clsc:
	clear;clear;

test_unordered:
	$(CC) $(CFLAGS) $(COPTS) -g -o test_unordered.out $(TEST_MAIN) $(TEST_DIR)/test_unordered.cpp $(SRC) $(LIBGTEST) -I$(TASTE_DIR) -I$(TEST_DIR)

test_expectmsg:
	$(CC) $(CFLAGS) $(COPTS) -g -o test_expectmsg.out $(TEST_MAIN) $(TEST_DIR)/test_expectmsg.cpp $(SRC) $(LIBGTEST) -I$(TASTE_DIR) -I$(TEST_DIR)

test_expectmsg_sleep:
	$(CC) $(CFLAGS) $(COPTS) -g -o test_expectmsg_sleep.out $(TEST_MAIN) $(TEST_DIR)/test_expectmsg_sleep.cpp $(SRC) $(LIBGTEST) -I$(TASTE_DIR) -I$(TEST_DIR)

clean:
	rm -f *.out
