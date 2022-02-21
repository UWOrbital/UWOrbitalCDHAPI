#lots of hardcoded stuff, will fix the hardcoding later, right now it is working

SRCS := src/*

INLCUDE_DIRS := -Ilibcsp/include
INLCUDE_DIRS += -Ilibcsp/build/include
INLCUDE_DIRS += -Llibcsp/build/
INLCUDE_DIRS += -Iinclude
INLCUDE_DIRS += -Iports/linux

LIBS := -lcsp
LIBS += -pthread

FLAGS := -Wall
FLAGS += -std=gnu99
FLAGS += -g

WAFFLAGS := --with-driver-usart=linux
WAFFLAGS += --enable-if-zmqhub

app:
	gcc -o app.out ${SRCS} ${FLAGS} ${INLCUDE_DIRS} ${LIBS}

ground:
	gcc -o ground.out ground_station/* ${FLAGS} ${INLCUDE_DIRS} ${LIBS}

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
