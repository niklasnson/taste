CC=g++
CFLAGS=-std=c++11
COPTS=-pthread
LIBGTEST=-I$(HOME)/Code/googletest/googletest/include $(HOME)/Code/googletest/googletest/build/libgtest.a $(HOME)/Code/googletest/googletest/build/libgtest_main.a

tests:
	$(CC) $(CFLAGS) $(COPTS) -o tests test_main.cpp $(LIBGTEST)

