CC = g++
LD = g++

CFLAGS = -Wall -fpie $(shell python3-config --cflags)
LFLAGS = -Wall $(shell python3-config --ldflags)

TESTE1OBJS = teste1.o
TESTE2OBJS = teste2.o 
TESTE3OBJS = teste3.o 
TESTE4OBJS = teste4.o 
MAINOBJS = main.o 

DRIVEPP = teste1\
		  teste2\
		  teste3\
		  teste4\
		  main

.cpp.o:
	$(CC) $(CFLAGS) -c $<

all: $(DRIVEPP)

teste1: $(TESTE1OBJS)
	$(LD) -o $@ $(TESTE1OBJS) $(LFLAGS)

teste2: $(TESTE2OBJS)
	$(LD) -o $@ $(TESTE2OBJS) $(LFLAGS)

teste3: $(TESTE3OBJS)
	$(LD) -o $@ $(TESTE3OBJS) $(LFLAGS)

teste4: $(TESTE4OBJS)
	$(LD) -o $@ $(TESTE4OBJS) $(LFLAGS) 

main: $(MAINOBJS)
	$(LD) -o $@ $(MAINOBJS) $(LFLAGS) 


clean:
	rm -f *.o $(DRIVEPP)

clean-objs:
	rm -f *.o
