CXXFLAGS=-ggdb
WATEROBJECTS=water.o Configuration.o solver.o WaterConf.o
CLOCKOBJECTS=clock.o Configuration.o solver.o ClockConf.o
JAMOBJECTS=jam.o Configuration.o JamConf.o
TARGETS=water clock jam
all: $(TARGETS)
clock: $(CLOCKOBJECTS)
	g++ -o clock $(CLOCKOBJECTS)
water: $(WATEROBJECTS)
	g++ -o water $(WATEROBJECTS)
jam: $(JAMOBJECTS)
	g++ -o jam $(JAMOBJECTS)
clock.o: solver.h ClockConf.h Configuration.h
water.o: solver.h WaterConf.h Configuration.h
jam.o: solver.h JamConf.h Configuration.h
Configuration.o: Configuration.h
solver.o: solver.h Configuration.h
ClockConf.o: ClockConf.h Configuration.h
WaterConf.o: WaterConf.h Configuration.h
JamConf.o: JamConf.h Configuration.h
clean:
	$(RM) *.o $(TARGETS)
