OUTPUTDIR = bin/
OBJSDIR = obj/

# Default compilation value
mode = debug

#To build libs, please run a 'make libs' first!
all: credentials dirs
	cd source; $(MAKE) mode=$(mode)

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
	mkdir -p data/gestures data/histograms

clean:
	cd source; $(MAKE) clean
	cd tool; $(MAKE) clean
	rm -Rf log

# Also delete histogram and gesture files
allclean:
	rm -Rf data