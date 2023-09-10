TARGET=./main.out
CC=g++
SRCS=\
	./main.cpp 
LIBS=\
	 -I /opt/homebrew/Cellar/libusb/1.0.26/include -L /opt/homebrew/Cellar/libusb/1.0.26/lib -lusb-1.0
    #-ljpeg # Добавить  -lmmal -lmmal_core -lmmal_util, если не будет работать

# На mac OS он не подтягивает автоматически библиотеки надо прямо путь указать
#JPEGLIB=-I /opt/homebrew/Cellar/jpeg-turbo/2.1.4/include -L /opt/homebrew/Cellar/jpeg-turbo/2.1.4/lib

STD=-std=c++17
#WER=#-Wall -Wextra -Werror -ansi

all: clean $(TARGET)

$(TARGET): 
	$(CC) -O3 $(STD) $(LIBS) -lm -o $(TARGET) $(SRCS)

build: $(TARGET)

clean:
	rm -rf $(TARGET)
