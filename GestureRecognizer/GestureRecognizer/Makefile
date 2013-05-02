# Gesture Recognition's Makefile
# Cesar Mora Castro
# 2013 - University of Minnesota

OUTPUTDIR = ./lib/
LIBNAME = libgesturerecognizer.so
OBJSDIR = ./obj/
INCDIR = ./include/
SRCDIR = ./source/
CXX = g++
CXXFLAGS = -Wall -c -fPIC -O2

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
OBJSCRUDE = HandDetector.o GestureRecognizer.o Recognizer.o Hand.o

OBJS= $(addprefix $(OBJSDIR),$(OBJSCRUDE))


# Rules
all:  dirs $(OUTPUTDIR)/$(LIBNAME) tool

tool: 
	cd tool; $(MAKE)	

$(OUTPUTDIR)/$(LIBNAME): $(OBJS)
	$(CXX) $(OBJS) -Wall $(LDFLAGS) $(INCFLAGS) -shared -o $(OUTPUTDIR)/$(LIBNAME)

install: $(OUTPUTDIR)/$(LIBNAME)
	cp $(OUTPUTDIR)/$(LIBNAME) /usr/lib/
	ldconfig

#Controller objs
$(OBJSDIR)%.o: $(SRCDIR)%.cpp $(INCDIR)%.h
	$(CXX) -o $@ $< $(CXXFLAGS) $(INCFLAGS) $(LDFLAGS)


#Controller objs
$(OBJSDIR)%.o: $(SRCDIR)Controllers/%.cpp $(INCDIR)Controllers/%.h
	$(CXX) -o $@ $< $(CXXFLAGS) $(INCFLAGS) $(LDFLAGS)

#Kernel objs
$(OBJSDIR)%.o: $(SRCDIR)Kernel/%.cpp $(INCDIR)Kernel/%.h
	$(CXX) -o $@ $< $(CXXFLAGS) $(INCFLAGS) $(LDFLAGS)

clean:
	rm -Rf $(OBJSDIR) $(OUTPUTDIR) *~

dirs:
	mkdir -p $(OUTPUTDIR)
	mkdir -p $(OBJSDIR)