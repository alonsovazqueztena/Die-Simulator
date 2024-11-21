# These are the user-space app variables.
TARGET_APP = dieApp
APP_OBJS = app.o hardware.o
CROSS_COMPILE = arm-linux-gnueabihf-
CC = $(CROSS_COMPILE)gcc
CFLAGS = -g -Wall -std=c99 -DDEBUG
LDFLAGS = -g -Wall

# The default target builds the user-space application.
.PHONY: all
all: $(TARGET_APP)

# This builds the user-space application.
$(TARGET_APP): $(APP_OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# This cleans the application.
.PHONY: clean
clean:
	rm -f $(TARGET_APP) *.o
