OBJECTS=clock.o Configuration.o solver.o
clock: $(OBJECTS)
	g++ -o clock $(OBJECTS)
clock.o: solver.h Configuration.h
Configuration.o: Configuration.h
solver.o: solver.h Configuration.h
