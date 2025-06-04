CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm
PWD = $(shell pwd)
INCLUDE_DIR = -I$(PWD)/header -I$(PWD)/dir_lev1 -I$(PWD)/dir_lev1/dir_lev2

SRCS = main.c
OBJS = $(SRCS:.c=.o)

LIB_SRCS = $(PWD)/dir_lev1/add.c $(PWD)/dir_lev1/dir_lev2/sub.c
LIB_OBJS = $(LIB_SRCS:.c=.o)
SLIB = scalc
DLIB = dcalc
SLIB_DIR = $(PWD)/slib
DLIB_DIR = $(PWD)/dlib
LFLAGS = -l
MAIN = main

all: $(MAIN)
	@echo Simple compiler named $(MAIN) has been compiled

# normal execution
$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -o $(MAIN) $(OBJS)

# static lib execution
slibexec: $(SLIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS)$(SLIB) -L$(SLIB_DIR) -o $(MAIN)

# dynamic lib execution
dlibexec: $(DLIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS)$(DLIB) -L$(DLIB_DIR) -o $(MAIN) -Wl,-rpath,$(DLIB_DIR)

# generate .o files for each .c file
# main.o: main.c
.c.o:
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -c $< -o $@

# make static lib
$(SLIB): $(LIB_OBJS)
	ar -rcs slib/lib$(SLIB).a $(LIB_OBJS)

# make dynamic lib
$(DLIB): $(LIB_OBJS)
	$(CC) -shared -fPIC -o dlib/lib$(DLIB).so $(LIB_OBJS)

.PHONY: clean

clean:
	rm -rf $(OBJS) $(LIB_OBJS) $(MAIN)

cleanall: clean
	rm -rf */*.so */*.a