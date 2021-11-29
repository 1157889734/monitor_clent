LIBS = -lpthread -ldrm

CCFLAGS = -c -g -fPIC
C++FLAGS = -c -g -fPIC

C_FILES = bo.c \
	  dev.c \
	  modeset.c \
	  rkdrm.c \
	  main.c rtspprotocolutil.c 

OBJS = \
       $(patsubst %.c,%.o,$(wildcard rkdrm/*.c))\
       $(patsubst %.c,%.o,$(wildcard *.c))

INCLUDES += -I/home/cftc/tools/RK3568/aarch64-buildroot-linux-gnu/sysroot/usr/include/libdrm

TARGET=rkdrm_demo

all:$(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -Wall -fPIC $(LIBS)


%.o:%.c
	$(CC) -c -o $@ $(@:.o=.c) $(CCFLAGS) $(INCLUDES)


clean:
	rm -f rkdrm_demo *.o

