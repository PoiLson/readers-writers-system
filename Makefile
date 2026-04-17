CC = gcc
LDFLAGS = -lpthread

BUILD = ./build
SRC = ./src

all: reader writer open close

reader:
	$(CC) $(SRC)/reader.c $(SRC)/customer.c $(SRC)/utilities.c -o $(BUILD)/reader $(LDFLAGS)

writer:
	$(CC) $(SRC)/writer.c $(SRC)/customer.c $(SRC)/utilities.c -o $(BUILD)/writer $(LDFLAGS)

open:
	$(CC) $(SRC)/open.c $(SRC)/customer.c $(SRC)/utilities.c -o $(BUILD)/open $(LDFLAGS)

close:
	$(CC) $(SRC)/close.c $(SRC)/customer.c $(SRC)/utilities.c -o $(BUILD)/close $(LDFLAGS)

clean:
	rm -f $(BUILD)/*