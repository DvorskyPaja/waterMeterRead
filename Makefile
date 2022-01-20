# Projekt: WaterMeter
# Autor:   Pavel Dvorsky
# Datum:   31.1.2020
# g++ gui_cpp_test.cpp -o gui_cpp_test -llept -ltesseract `pkg-config --cflags --libs opencv`
CC=g++
OS=$(shell lsb_release -si)
ifeq ($(OS),Ubuntu)
    # - g means compile and assembly do not link
	CFLAGS=-DCAMERA_PRESENT=0 -g `pkg-config --cflags --libs opencv4`
	CFLAGS2 = `pkg-config --libs opencv4` -llept -ltesseract 	
#CFLAGS=$(shell pkg-config --cflags --libs opencv4) #-std=c99 -pedantic -Wall -Wextra -g
else
	CFLAGS=-DCAMERA_PRESENT=1 `pkg-config --cflags --libs opencv` #-std=c99 -pedantic -Wall -Wextra -g
	CFLAGS2=-llept -ltesseract -lwiringPi	
endif

NAME= main
#CFLAGS +=    # make variable visible for preprocessor

OBJS = Directory.o imageIn.o 
#g++ -std=c++11 main.cpp -o test pkg-config opencv4 --cflags --clibs
all: $(NAME)

$(OBJS):%.o: %.cpp
	@echo "Building obj files"
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(NAME).cpp $(OBJS)
	@echo "Building for $(OS)"	
#	$(CC) $(CFLAGS) $(NAME).cpp -o $(NAME) -llept -ltesseract	
	$(CC) $(CFLAGS) $(NAME).cpp $(OBJS) -o $(NAME) $(CFLAGS2) 

clean:
	rm -f $(NAME)

very_clean:
	rm -f $(NAME)
	rm -f *.png
	rm -f *.log
	rm -f *.o
