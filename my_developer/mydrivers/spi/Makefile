
VPATH = CMSIS
CC=$(CROSS_COMPILE_APPS)gcc
CFLAGS		:= -Os -mcpu=cortex-m3 -mthumb
LDFLAGS		:= -mcpu=cortex-m3 -mthumb -I CMSIS
SOURCES=drivers/mss_spi/mss_spi.c lmk04800.c main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=test
ifeq ($(OS),Windows_NT)
   RM = del /Q
else
   RM = rm -rf
endif

all: clean $(EXECUTABLE) cleano_bjetcs

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE) $(EXECUTABLE).o
	
cleano_bjetcs:
	$(RM) $(OBJECTS)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@  -lm
