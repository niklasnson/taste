CC=g++
CFLAGS=-std=c++11
SRC=client.cpp inbox.h message.cpp main.cpp
NAME=taste.out

taste:
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

run: clean taste
	@echo "Running ..."
	@echo ""
	./taste.out

clean:
	rm -f *.out
