#  Ian micheal Update simple wavfile playing example using bluecrabs example 
#I did this by request it's based on Lawrence Sebald example just to show it playing a wav file*
# KallistiOS ##version##
# Based on sdl/sound/example.c By Copyright (C) 2016 Lawrence Sebald  
# Update to play simple wav Copyright (C) 2016 Ian micheal
# (c)2001 Dan Potter
# Copyright (C) 2016 Lawrence Sebald  
# Copyright (C) 2016 Ian micheal
TARGET = playwav.elf
BIN = playwav.bin
FIRSTREAD = playwav.bin

OPT= -funroll-loops 
# Version with Null sound system
KOS_LOCAL_CFLAGS =  -DMAXSEG_64K   -DSDL -DLSB_FIRST -DALIGN_LONG -DINLINE -DDC -DUCHAR_MAX=0xff -DUSHRT_MAX=0xffff -DULONG_MAX=0xffffffff
KOS_CFLAGS += $(OPT)
# Version with Null sound system
OBJS = playwav.o
all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

clean:
	-rm -f $(TARGET) $(BIN) $(FIRSTREAD) $(OBJS) romdisk.*

rm-elf:
	-rm -f $(TARGET) romdisk.*

$(TARGET): $(OBJS) romdisk.o
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET) $(KOS_START) \
		$(OBJS) romdisk.o $(OBJEXTRA) -L$(KOS_BASE)/lib  -lSDL-1.2.9  -lpng -lz -lm  -lkallisti -llwip4 -lc -ldcplib -lk++  $(KOS_LIBS)

romdisk.img:
	$(KOS_GENROMFS) -f romdisk.img -d romdisk -v

romdisk.o: romdisk.img
	$(KOS_BASE)/utils/bin2o/bin2o romdisk.img romdisk romdisk.o

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)

dist:
	rm -f $(OBJS) romdisk.o romdisk.img
	$(KOS_STRIP) $(TARGET)
	$(KOS_CC_BASE)/bin/sh-elf-objcopy -O binary $(TARGET) $(BIN)
	$(KOS_CC_BASE)/bin/sh-elf-scramble $(BIN) $(FIRSTREAD)
	cp $(FIRSTREAD) 1st_read.bin
