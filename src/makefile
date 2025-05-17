SYSCONF_LINK = g++
IDIR = ../include
ODIR = ./obj
LDIR = ../lib
BINDIR = ../bin

CFLAGS = -I$(IDIR)
LIBS = -lm -DUNICODE 

DEPS = $(wildcard $(IDIR)/*.h)
$(info > Searching header files: [$(DEPS)])

OBJ = $(wildcard *.cpp) $(wildcard $(IDIR)/*.cpp)
$(info > Searching Object files: [$(OBJ)])

$(ODIR)/%.o: %.cpp $(DEPS)
	$(SYSCONF_LINK) -c -o $@ $< $(CFLAGS)

release_mode: $(OBJ)
	$(SYSCONF_LINK) -o ../bin/$@ $^ $(CFLAGS) $(LIBS) 

debug_mode: $(OBJ)
	$(SYSCONF_LINK) -D _DEBUG -o ../bin/$@ $^ $(CFLAGS) $(LIBS) 
.PHONY: clean


clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
#g++ main.cpp ../include/tgaimage.cpp -o ../bin/main.o -I ../include