
CC = g++
CFLAGS = -c -std=c++11 -g
LDFLAGS = -g
SRC = ${wildcard src/*.cpp}
HDR = ${wildcard include/*.hpp}
OBJ = ${SRC:.cpp=.obj}
EXEC = interpreter

all: ${SRC} ${OBJ} ${EXEC}

debug: all
debug: CFLAGS += DDEBUG		



${EXEC}: ${OBJ}
	@${CC} ${LDFLAGS} $^ -o $@
	@echo made EXEC $@
%.obj: %.cpp ${HDR}

	@${CC} ${CFLAGS} $< -o $@

	@echo made object $@

clean:
	rm src/*.obj ${EXEC}


  	



