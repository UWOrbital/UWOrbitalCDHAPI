#lots of hardcoded stuff, will fix the hardcoding later, right now it is working

SRCS := src/*

INCLUDE_DIRS := -Ilibcsp/include
INCLUDE_DIRS += -Ilibcsp/build/include
INCLUDE_DIRS += -Llibcsp/build/
INCLUDE_DIRS += -Iinclude
INCLUDE_DIRS += -Iports/linux

LIBS := -lcsp
LIBS += -pthread

FLAGS := -Wall
FLAGS += -std=gnu99
FLAGS += -g

WAFFLAGS := --with-driver-usart=linux
WAFFLAGS += --enable-if-zmqhub

all: app ground

app:
	gcc -o app.out ${SRCS} ${FLAGS} ${INCLUDE_DIRS} ${LIBS}

ground:
	gcc -o ground.out ground_station/* ${FLAGS} ${INCLUDE_DIRS} ${LIBS}

libcsp: FORCE
	cd libcsp; \
	./waf configure build install ${WAFFLAGS}; \
	cd ..

libcsp-clean: FORCE
	cd libcsp; \
	./waf distclean
	cd ..

FORCE:

clean:
	rm -r *.o *.out
