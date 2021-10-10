CC = g++
LD = g++

CFLAGS = -Wall -I/usr/include/python3.6
LFLAGS = -Wall 

TESTEINICIALOBJS = main.o 

DRIVEPP = testeInicial

.cpp.o:
	$(CC) $(CFLAGS) -c $<

all: $(DRIVEPP)

testeInicial: $(TESTEINICIALOBJS)
	$(LD) $(LFLAGS) -o $@ $(TESTEINICIALOBJS) -lm

clean:
	rm -f *.o $(DRIVEPP)

clean-objs:
	rm -f *.o