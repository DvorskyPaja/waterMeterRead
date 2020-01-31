# Projekt: WaterMeter
# Autor:   Pavel Dvorsky
# Datum:   31.1.2020
# g++ gui_cpp_test.cpp -o gui_cpp_test -llept -ltesseract `pkg-config --cflags --libs opencv`
CC=g++
CFLAGS= #-std=c99 -pedantic -Wall -Wextra -g
NAME= gui_cpp_test

$(NAME): $(NAME).cpp
	$(CC) $(NAME).cpp -o $(NAME) -llept -ltesseract `pkg-config --cflags --libs opencv`
clean:
	rm -f $(NAME)

very_clean:
	rm -f gui_cpp_test
	rm -f *.png
	rm -f *.log
	rm -f ../*.txt