PRODUCT=sluice

CFLAGS=-Wall -Werror -Wextra -pedantic -ggdb -O0 -Icode -Icode/interfaces

SOURCES=$(wildcard code/*.cpp)
HEADERS=$(wildcard code/*.h) \
        $(wildcard code/interfaces/*.h)

CC=g++

.phony: all clean

all: $(PRODUCT)

$(PRODUCT): $(SOURCES) $(HEADERS) Makefile
	@$(CC) $(CFLAGS) $(SOURCES) -o $@

clean:
	@rm -rf $(PRODUCT)
