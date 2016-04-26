#Adapted from Colfax webinars on Xeon Phi

CXX = icc #set this to icpc if you are using C++
CXXFLAGS=-fopenmp
CPUFLAGS = $(CXXFLAGS) -xhost
MICFLAGS = $(CXXFLAGS) -mmic

CPUOBJECTS = mm_tile.o
MICOBJECTS = mm_tile.oMIC

TARGET=app-CPU app-MIC

.SUFFIXES: .o .cc .oMIC

all: $(TARGET) instructions

app-CPU: $(CPUOBJECTS)
        $(CXX) $(CPUFLAGS) -o $@ $(CPUOBJECTS)

app-MIC: $(MICOBJECTS)
        $(CXX) $(MICFLAGS) -o $@ $(MICOBJECTS)

.cc.o:
      	$(CXX) -c $(CPUFLAGS) $(OPTFLAGS) -o "$@" "$<"

.cc.oMIC:
	$(CXX) -c $(MICFLAGS) $(OPTFLAGS) -o "$@" "$<"

instructions:
	$(info )
        $(info TO EXECUTE THE APPLICATION: )
        $(info "make run-cpu" to run the application on the host CPU)
        $(info "make run-mic" to run the application on the coprocessor)
        $(info )

run-cpu: app-CPU
        ./app-CPU a "100 2"

run-mic: app-MIC
        micnativeloadex ./app-MIC -a "10 2 2"
clean:
      	rm -f $(CPUOBJECTS) $(MICOBJECTS) $(TARGET)