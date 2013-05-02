# Test app for Gesture Recognizer - Makefile
# Cesar Mora Castro
# 2013 - University of Minnesota

OUTPUTDIR = ./bin/
OBJSDIR = ./obj/
SRCDIR = ./src/
CXX = g++
CXXFLAGS = -Wall -c -O2

# Compilation mode
ifeq ($(mode), release) # Release mode
	CXXFLAGS += -O2
else # Debug mode
	CXXFLAGS += -ggdb
endif

# Libraries
LDFLAGS = -lSDL  `pkg-config --libs opencv` -LGestureRecognizer/lib -lgesturerecognizer

# Includes
INCFLAGS = -I$(INCDIR) `pkg-config --cflags sdl` -IGestureRecognizer/include

# Objects
OBJSCRUDE = EndController.o InputEventController.o Logger.o VideoFactory.o\
			VideoSource.o World.o main.o

OBJS= $(addprefix $(OBJSDIR),$(OBJSCRUDE))

# Rules
all: credentials dirs libs $(OUTPUTDIR)/test

$(OUTPUTDIR)/test: $(OBJS)
	$(CXX) $(OBJS) -Wall $(LDFLAGS) $(INCFLAGS) -o $(OUTPUTDIR)/test


$(OBJSDIR)main.o: $(SRCDIR)main.cpp
	$(CXX) -o $@ $< $(CXXFLAGS) $(INCFLAGS) $(LDFLAGS)


$(OBJSDIR)%.o: $(SRCDIR)%.cpp $(SRCDIR)%.h
	$(CXX) -o $@ $< $(CXXFLAGS) $(INCFLAGS) $(LDFLAGS)

install:
	cd GestureRecognizer; $(MAKE) install
	
clean:
	rm -Rf $(OBJSDIR) $(OUTPUTDIR) *~
	rm -Rf log
	cd GestureRecognizer; $(MAKE) clean


# Build gesture recognizer
libs:
	cd GestureRecognizer; $(MAKE) $(mode)

credentials:
	@echo
	@echo '--------------------------------------'
	@echo ' Gesture Recognition Makefile'
	@echo ' Cesar Mora Castro - 2013 University of Minnesota'
	@echo ' Compiling $(mode) mode'
	@echo '--------------------------------------'
	@echo

dirs:
	mkdir -p $(OUTPUTDIR)
	mkdir -p $(OBJSDIR)