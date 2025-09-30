CSRCS = helloworld.cpp log.cpp
EXECUTABLE = helloworld
LDFLAGS = -lstdc++
all: 
	gcc ${CSRCS} ${LDFLAGS} -o ${EXECUTABLE}

run: helloworld
	./${EXECUTABLE}

clean:
	rm -f *.o 
	rm -f ${EXECUTABLE}