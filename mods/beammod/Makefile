OBJS=mod_main.o

CFLAGS=-shared -fPIC -Wall

all: ../beam.so

../beam.so: $(OBJS)
	$(CC)   $^ -o $@ $(CFLAGS) 
clean:
	-rm ../beam.so *.o