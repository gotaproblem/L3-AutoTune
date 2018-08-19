CC		= gcc
CFLAGS	= -Wall -I. -s
DEPS 	= at.h
OBJ 	= at.o vSet.o pic.o vFrequency.o profiles.o readAPI.o readDelay.o vFan.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

at: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o *~ core 

