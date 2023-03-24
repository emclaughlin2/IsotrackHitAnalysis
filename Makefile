CC = g++
ROOTCONFIG = `root-config --libs --cflags`
BOOST = -L/opt/sphenix/core/boost/lib -lboost_program_options
HEADERS = *.h modules/*.h selections/*.h
SOURCES = IsotrackHitAnalysis.C run.C 
EXECUTABLE = ../hit-build/run_analysis

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES) $(HEADERS)
	$(CC) $(SOURCES) $(ROOTCONFIG) -o $(EXECUTABLE) $(BOOST)
