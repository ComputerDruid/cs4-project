WATEROBJECTS=water.o Configuration.o solver.o WaterConf.o
CLOCKOBJECTS=clock.o Configuration.o solver.o ClockConf.o
TARGETS=water clock
all: $(TARGETS)
clock: $(CLOCKOBJECTS)
	g++ -o clock $(CLOCKOBJECTS)
water: $(WATEROBJECTS)
	g++ -o water $(WATEROBJECTS)
clock.o: solver.h ClockConf.h Configuration.h
water.o: solver.h ClockConf.h Configuration.h
Configuration.o: Configuration.h
solver.o: solver.h Configuration.h
ClockConf.o: ClockConf.h Configuration.h
WaterConf.o: WaterConf.h Configuration.h
clean:
	$(RM) *.o $(TARGETS)
