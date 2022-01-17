# Projekt: WaterMeter
# Autor:   Pavel Dvorsky
# Datum:   31.1.2020
# g++ gui_cpp_test.cpp -o gui_cpp_test -llept -ltesseract `pkg-config --cflags --libs opencv`
CC=g++
OS=$(shell lsb_release -si)
ifeq ($(OS),Ubuntu)
    # - g means compile and assembly do not link
	CFLAGS=-g `pkg-config --cflags --libs opencv4`
	CFLAGS2 = `pkg-config --libs opencv4` -llept -ltesseract 	
#CFLAGS=$(shell pkg-config --cflags --libs opencv4) #-std=c99 -pedantic -Wall -Wextra -g
else
	CFLAGS=`pkg-config --cflags --libs opencv` #-std=c99 -pedantic -Wall -Wextra -g
	CFLAGS2=-llept -ltesseract	
endif

NAME= main

#g++ -std=c++11 main.cpp -o test pkg-config opencv4 --cflags --clibs

$(NAME): $(NAME).cpp
	@echo "Building for $(OS)"	
#	$(CC) $(CFLAGS) $(NAME).cpp -o $(NAME) -llept -ltesseract	
	$(CC) $(CFLAGS) $(NAME).cpp -o $(NAME) $(CFLAGS2) 	



clean:
	rm -f $(NAME)

very_clean:
	rm -f $(NAME)
	rm -f *.png
	rm -f *.log