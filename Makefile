CC=g++
CFLAGS=-std=c++14
COPTS=-pthread
LIBGTEST=-I$(HOME)/Code/googletest/googletest/include $(HOME)/Code/googletest/googletest/build/libgtest.a $(HOME)/Code/googletest/googletest/build/libgtest_main.a

TASTE_DIR=taste
SRC=$(TASTE_DIR)/client.cpp $(TASTE_DIR)/message.cpp

TEST_DIR=tests
TEST_MAIN=$(TEST_DIR)/test_main.cpp

all: test_solutions

test_solutions:
	$(CC) $(CFLAGS) $(COPTS) -g -o test_solutions.out $(TEST_MAIN) $(TEST_DIR)/test_solutions.cpp $(SRC) $(LIBGTEST) -I$(TASTE_DIR) -I$(TEST_DIR)

run_solutions:
	./test_solutions.out

clean:
	rm -f *.out
