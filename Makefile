CXXFLAGS=-ggdb
WATEROBJECTS=water.o Configuration.o solver.o WaterConf.o
CLOCKOBJECTS=clock.o Configuration.o solver.o ClockConf.o
JAMOBJECTS=jam.o Configuration.o JamConf.o
WORDSOBJECTS=words.o Configuration.o solver.o WordsConf.o
TARGETS=water clock jam words
all: $(TARGETS)
clock: $(CLOCKOBJECTS)
	g++ -o clock $(CLOCKOBJECTS)
water: $(WATEROBJECTS)
	g++ -o water $(WATEROBJECTS)
jam: $(JAMOBJECTS)
	g++ -o jam $(JAMOBJECTS)
words: $(WORDSOBJECTS)
	g++ -o words $(WORDSOBJECTS)
clock.o: solver.h ClockConf.h Configuration.h
water.o: solver.h WaterConf.h Configuration.h
jam.o: solver.h JamConf.h Configuration.h
words.o: solver.h WordsConf.h Configuration.h
Configuration.o: Configuration.h
solver.o: solver.h Configuration.h
ClockConf.o: ClockConf.h Configuration.h
WaterConf.o: WaterConf.h Configuration.h
JamConf.o: JamConf.h Configuration.h
WordsConf.o: WordsConf.h Configuration.h
clean:
	$(RM) *.o $(TARGETS)
