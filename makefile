CC = gcc
CFLAGS = -Wall -O3
TARGET = Ort
SOURCES = geral.c mode1.c mode2.c mode3.c

all:
	$(CC) $(FLAGS) -g $(SOURCES) $(TARGET).c -o $(TARGET)

clean:
	del $(TARGET).exe