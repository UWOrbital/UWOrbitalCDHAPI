#lots of hardcoded stuff, will fix the hardcoding later, right now it is working

SRCS := src/*

INLCUDE_DIRS := -Ilibcsp/include
INLCUDE_DIRS += -Ilibcsp/build/include
INLCUDE_DIRS += -Iinclude
INLCUDE_DIRS += -Iports/linux

LIBS := -lcsp

FLAGS := -Wall
FLAGS += -std=gnu99
FLAGS += -g


app:
	gcc ${SRCS} ${FLAGS} ${INLCUDE_DIRS} ${LIBS}

ground:
	gcc ground_station/* ${FLAGS} ${INLCUDE_DIRS} ${LIBS}

clean:
	rm -r *.o *.out
