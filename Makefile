CC=g++
CFLAGS=-std=c++11
COPTS=-pthread
LIBGTEST=-I$(HOME)/Code/googletest/googletest/include $(HOME)/Code/googletest/googletest/build/libgtest.a $(HOME)/Code/googletest/googletest/build/libgtest_main.a

TASTE_DIR=taste
SRC=$(TASTE_DIR)/client.cpp $(TASTE_DIR)/server.cpp $(TASTE_DIR)/package.cpp

TEST_DIR=tests
TEST_MAIN=$(TEST_DIR)/test_main.cpp

all: test_deterministic

test_deterministic:
	$(CC) $(CFLAGS) $(COPTS) -o test_deterministic.out $(TEST_MAIN) $(TEST_DIR)/test_deterministic.cpp $(SRC) $(LIBGTEST) -I$(TASTE_DIR)

clean:
	rm -f *.out
