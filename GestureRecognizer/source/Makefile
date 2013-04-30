# Gesture Recognition's Makefile
# Cesar Mora Castro
# 2013 - University of Minnesota

OUTPUTDIR = ../bin/
OBJSDIR = ../obj/
INCDIR = ../include/
SRCDIR = ./
CXX = g++
CXXFLAGS = -Wall -c -O2

# Compilation mode
ifeq ($(mode), release) # Release mode
	CXXFLAGS += -O2
else # Debug mode
	CXXFLAGS += -ggdb
endif

# Libraries
LDFLAGS = -lSDL  `pkg-config --libs opencv`

# Includes
INCFLAGS = -I$(INCDIR) `pkg-config --cflags sdl`

# Objects
OBJSCRUDE = HandDetector.o InputEventController.o GestureRecognizer.o VideoFactory.o Logger.o VideoSource.o \
	World.o EndController.o

OBJS= $(addprefix $(OBJSDIR),$(OBJSCRUDE))


# Rules
all:  $(OUTPUTDIR)/gesturerec

$(OUTPUTDIR)/gesturerec: $(SRCDIR)gesturerec.cpp $(OBJS)
	$(CXX) $(OBJS) gesturerec.cpp -Wall $(LDFLAGS) $(INCFLAGS) -o $(OUTPUTDIR)/gesturerec


#Controller objs
$(OBJSDIR)%.o: $(SRCDIR)Controllers/%.cpp $(INCDIR)Controllers/%.h
	$(CXX) -o $@ $< $(CXXFLAGS) $(INCFLAGS) $(LDFLAGS)

#Factories objs
$(OBJSDIR)%.o: $(SRCDIR)Factories/%.cpp $(INCDIR)Factories/%.h
	$(CXX) -o $@ $< $(CXXFLAGS) $(INCFLAGS) $(LDFLAGS)

#Kernel objs
$(OBJSDIR)%.o: $(SRCDIR)Kernel/%.cpp $(INCDIR)Kernel/%.h
	$(CXX) -o $@ $< $(CXXFLAGS) $(INCFLAGS) $(LDFLAGS)

#Kernel/TrackingMethods objs
$(OBJSDIR)%.o: $(SRCDIR)Kernel/TrackingMethods/%.cpp $(INCDIR)Kernel/TrackingMethods/%.h
	$(CXX) -o $@ $< $(CXXFLAGS) $(INCFLAGS) $(LDFLAGS)

clean:
	rm -Rf $(OBJSDIR) $(OUTPUTDIR) *~