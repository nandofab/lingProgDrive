CC = g++
LD = g++

CFLAGS = -Wall -fpie $(shell python3-config --cflags --embed) 
LFLAGS = -Wall $(shell python3-config --ldflags --embed)

TESTE1OBJS = teste1.o
TESTE2OBJS = teste2.o 
TESTE3OBJS = teste3.o 
TESTE4OBJS = teste4.o 
DRIVEPPOBJS = Drivepp.o main.o MimeTypes.o

DRIVEPP = teste1\
		  teste2\
		  teste3\
		  teste4\
		  Drivepp

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

Drivepp: $(DRIVEPPOBJS)
	$(LD) -o $@ $(DRIVEPPOBJS) $(LFLAGS) 

clean:
	rm -f *.o $(DRIVEPP)

clean-objs:
	rm -f *.o