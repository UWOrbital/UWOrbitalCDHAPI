

SRCS := src/*

INLCUDE_DIRS := -Ilibcsp/include
INLCUDE_DIRS += -Ilibcsp/build/include
INLCUDE_DIRS += -Iinclude
INLCUDE_DIRS += -Iports/linux

LIBS := -lcsp

FLAGS := -Wall

all:
	gcc ${SRCS} ${FLAGS} ${INLCUDE_DIRS} ${LIBS} 

clean:
	rm -r *.o *.out